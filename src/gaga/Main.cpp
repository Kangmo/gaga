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
	int gene_fence_values[] = {2, 40, 50, 6000, 50, 70, 200};
	EntityMeta entityMeta( sizeof(gene_fence_values)/ sizeof(gene_fence_values[0]), gene_fence_values  );

	int solution[] = {1, 31, 39, 4589, 38, 27, 38};
	int number_of_genes = sizeof(solution) / sizeof(solution[0]);

	assert(number_of_genes == entityMeta.get_gene_count());

	const int MINIMUM_SCORE_REQUIREMENT_FOR_SOLUTION = 10;

	Problem problem(number_of_genes, solution, MINIMUM_SCORE_REQUIREMENT_FOR_SOLUTION );

	EcoSystem ecoSystem(50, // population
			            5,  // dominant candidate count
			            true, // keep best entity
			            entityMeta);

	Entity * solver = ecoSystem.evolve( problem, [](int generation, const Entity & best_entity) {
		std::cout << "Generation " << generation << ", best entity : " << best_entity.to_string() << std::endl;
	});

	if (solver) {
		std::cout << "Yeah! finally the following entity solved the problem !" << std::endl;
		std::cout << "entity : " << solver->to_string() << std::endl;
	}
}
