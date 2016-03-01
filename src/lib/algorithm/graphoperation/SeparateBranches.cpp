/*
Copyright (c) 2016 Bastien Durix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


/**
 *  \file SeparateBranches.cpp
 *  \brief Defines function to separate skeleton in different branches
 *  \author Bastien Durix
 */

#include "SeparateBranches.h"

template<typename Model>
typename skeleton::ComposedCurveSkeleton<skeleton::GraphBranch<Model> >::Ptr SeparateBranches_helper(const typename skeleton::GraphCurveSkeleton<Model>::Ptr grskel)
{
	// nodes identifiants 
	std::vector<unsigned int> vec_nodeid(0);
	grskel->getAllNodes(vec_nodeid);
	
	// set how many times they are used
	std::vector<bool> used(vec_nodeid.size(),false);
	
	// container of starting points
	std::list<unsigned int> extremities;
	grskel->getNodesByDegree(1,extremities);
	
	// branches containers
	std::list<std::pair<Eigen::Matrix<unsigned int,2,1>,std::list<unsigned int> > > compskel;

	/*
	 *  For each extremity, we traverse the graph to estimate the branch starting from this extremity
	 */
	for(std::list<unsigned int>::iterator ext = extremities.begin(); ext != extremities.end(); ext++)
	{
		std::list<unsigned int> cur_branch; // contains the nodes indices
		unsigned int cur_nod = *ext,
					 prev_nod = *ext;
		bool finished = false;
		/*
		 *  Traversing the branch
		 */
		while(!finished)
		{
			// indice of the current node in the graph skeleton
			unsigned int ind_cur_nod = std::find(vec_nodeid.begin(),vec_nodeid.end(),cur_nod) - vec_nodeid.begin();
			cur_branch.push_back(cur_nod);
			
			// mark the node
			used[ind_cur_nod]=true;
			
			// current node neighbors
			std::vector<unsigned int> neigh(0);
			grskel->getNeighbors(cur_nod,neigh);

			if(neigh.size() == 2) // basis case : continue
			{
				if(neigh[0] == prev_nod)
				{
					prev_nod = cur_nod;
					cur_nod = neigh[1];
				}
				else
				{
					prev_nod = cur_nod;
					cur_nod = neigh[0];
				}
			}
			else if(neigh.size() == 1) // extremity case
			{
				// indice of current neighbor
				unsigned int ind_neigh = std::find(vec_nodeid.begin(),vec_nodeid.end(),neigh[0]) - vec_nodeid.begin();
				if(!used[ind_neigh] || grskel->getNodeDegree(neigh[0]) > 2) // if next node is not used, or degree more than 2, continue
				{
					prev_nod=cur_nod;
					cur_nod=neigh[0];
				}
				else
				{
					finished=true;
				}
			}
			else // junction case
			{
				if(prev_nod == cur_nod) // current node == first node
				{
					finished=true;
					for(unsigned int i = 0; i<neigh.size() && finished; i++) // test if there is a branch starting from this point
					{
						unsigned int ind_neigh = std::find(vec_nodeid.begin(),vec_nodeid.end(),neigh[i]) - vec_nodeid.begin();
						if(!used[ind_neigh])
						{
							prev_nod=cur_nod;
							cur_nod=neigh[i];
							finished=false;
						}
					}

				}
				else // current node == ending point
				{
					for(unsigned int i = 0; i<neigh.size(); i++) // adds the ending node if there is still new branches starting from it
					{
						unsigned int ind_neigh = std::find(vec_nodeid.begin(),vec_nodeid.end(),neigh[i]) - vec_nodeid.begin();
						if(!used[ind_neigh])
						{
							extremities.push_back(cur_nod);
						}
					}
					finished=true;
				}
			}
		}

		if(prev_nod != cur_nod) // adds the branch to the composed skeleton
		{
			compskel.push_back(std::pair<Eigen::Matrix<unsigned int,2,1>,std::list<unsigned int> >(Eigen::Matrix<unsigned int,2,1>(*ext,cur_nod),cur_branch));
		}
	}

	std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int> > > map_links;
	
	// get the extremities/junctions of the skeleton
	extremities.clear();
	for(std::list<std::pair<Eigen::Matrix<unsigned int,2,1>,std::list<unsigned int> > >::iterator branch = compskel.begin(); branch != compskel.end(); branch++)
	{
		extremities.push_back(branch->first(0));
		extremities.push_back(branch->first(1));
	}
	extremities.sort();
	extremities.unique();
	
	// creates the composed skeleton
	typename skeleton::ComposedCurveSkeleton<skeleton::GraphBranch<Model> >::Ptr 
		skelres(new typename skeleton::ComposedCurveSkeleton<skeleton::GraphBranch<Model> >());
	
	// adds the extremities in the composed skeleton
	std::vector<unsigned int> vec_ext(extremities.begin(),extremities.end());
	for(unsigned int i=0;i<extremities.size();i++)
	{
		skelres->addNode(i);
	}

	// construct the branches
	for(std::list<std::pair<Eigen::Matrix<unsigned int,2,1>,std::list<unsigned int> > >::iterator branch = compskel.begin(); branch != compskel.end(); branch++)
	{
		// nodes in the skeleton
		std::vector<typename Model::Stor> vec_br(0);
		grskel->getNodes(branch->second,vec_br);
		
		//create the branch
		skeleton::GraphBranch<Model> disbranch(grskel->getModel(),vec_br);
		
		// compute the extremities
		unsigned int ext1 = std::find(vec_ext.begin(),vec_ext.end(),branch->first(0))-vec_ext.begin();
		unsigned int ext2 = std::find(vec_ext.begin(),vec_ext.end(),branch->first(1))-vec_ext.begin();
		
		// adds the branch, associated to the extremities
		skelres->addEdge(ext1,ext2,disbranch);
	}

	return skelres;
}

typename skeleton::CompGraphSkel2d::Ptr algorithm::graphoperation::SeparateBranches(const typename skeleton::GraphSkel2d::Ptr grskel)
{
	return SeparateBranches_helper<skeleton::model::Classic<2> >(grskel);
}

typename skeleton::CompGraphSkel3d::Ptr algorithm::graphoperation::SeparateBranches(const typename skeleton::GraphSkel3d::Ptr grskel)
{
	return SeparateBranches_helper<skeleton::model::Classic<3> >(grskel);
}

typename skeleton::CompGraphProjSkel::Ptr algorithm::graphoperation::SeparateBranches(const typename skeleton::GraphProjSkel::Ptr grskel)
{
	return SeparateBranches_helper<skeleton::model::Projective>(grskel);
}	