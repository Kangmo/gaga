/*
 * Main.cpp
 *
 *  Created on: 2013. 9. 18.
 *      Author: ilvsusie
 */



#include <memory>
#include <iostream>
#include "Problem.h"
#include "EcoSystem.h"
#include "Entity.h"
#include <assert.h>

int main(int argc, const char * argv[])
{
//	int gene_fence_values[] = {2, 40, 50, 6000, 50, 70, 200};
	int gene_fence_values[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
			                   10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
			                   10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
			                   10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
			                   10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	EntityMeta entityMeta( sizeof(gene_fence_values)/ sizeof(gene_fence_values[0]), gene_fence_values  );

	int solution[] = {1, 3, 5, 7, 9, 4, 0, 3, 1, 8,
			          5, 7, 3, 2, 8, 9, 3, 6, 6, 0,
	                  5, 3, 2, 6, 8, 2, 1, 0, 9, 9,
	                  5, 2, 4, 2, 6, 1, 2, 6, 3, 0,
	                  9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	int number_of_genes = sizeof(solution) / sizeof(solution[0]);

	assert(number_of_genes == entityMeta.get_gene_count());

	int max_score = Problem::get_max_score(entityMeta);

	// If we get the 100% of the maximum score, we solved the problem!
	int minimum_score_requirement = (int)((float)max_score * 1);

	const Problem problem(number_of_genes, solution, minimum_score_requirement );


	EcoSystem ecoSystem(50, // population
			            5,  // dominant candidate count
			            false, // keep best entity
			            entityMeta);

	Entity * solver = ecoSystem.evolve( problem,
			                            20000,
			                            [=](int generation, const Entity & best_entity) {
		float error_ratio = ((float)(max_score-best_entity.get_score())) / (float)max_score;

		std::cout << "Generation " << generation << ", best entity : " << best_entity.to_string() << std::endl;

		std::cout << "Error ratio : " << error_ratio << std::endl;
	});

	if (solver) {
		std::cout << "Yeah! finally the following entity solved the problem !" << std::endl;
		std::cout << "entity : " << solver->to_string() << std::endl;
	}
}
