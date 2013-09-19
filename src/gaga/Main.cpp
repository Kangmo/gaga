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
	int gene_fence_values[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
			                   100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
			                   100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
			                   100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
			                   100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

	EntityMeta entityMeta( sizeof(gene_fence_values)/ sizeof(gene_fence_values[0]), gene_fence_values  );

	int solution[] = {38, 26, 91, 48,  2, 48, 39, 69, 91, 48,
			          0,  28, 34, 39, 91, 83, 68, 38, 18, 69,
			          68, 27, 31, 58, 55, 22, 19, 18, 49, 12,
			          16, 19, 11, 47, 70, 10, 58, 11, 69, 28,
			          68, 17, 68, 27, 78, 69, 90, 99,  0, 77 };
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
