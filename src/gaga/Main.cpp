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
	int gene_fence_values[] = {10,  250, 3500, 20, 60, 500, 10,   2, 50, 1000,
	                           3000, 200, 900, 10, 20, 150,100,8000, 10,   25};

	EntityMeta entityMeta( sizeof(gene_fence_values)/ sizeof(gene_fence_values[0]), gene_fence_values  );

	int solution[] = {    3,  176, 2781, 19, 53, 499,   0,    1, 49, 186,
			            216,  117, 841,  2,   0, 111,  91, 7391,  3, 19 };

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
