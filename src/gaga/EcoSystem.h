/*
 * EcoSystem.h
 *
 *  Created on: 2013. 9. 18.
 *      Author: ilvsusie
 */

#ifndef ECOSYSTEM_H_
#define ECOSYSTEM_H_

#include "Entity.h"
#include "Problem.h"
#include "Population.h"
#include <functional>

typedef std::function<void(int generation, const Entity & best_entity)> on_evolution_t;

class EcoSystem {
public:
	EcoSystem(int a_population, int a_domiant_candidate_count, bool a_keep_best_entity, const EntityMeta & a_entity_meta)
		: entity_meta(a_entity_meta) {

		domiant_candidate_count = a_domiant_candidate_count;
		keep_best_entity = a_keep_best_entity;

		population = new Population(a_entity_meta);
		population->populate(a_population);

	}

	virtual ~EcoSystem() {

	}

	Entity * evolve(const Problem & problem, int max_generation, on_evolution_t on_evolution) {

		bool solved = false;

		std::shared_ptr<Entity> best_entity;
		for (int generation=1; generation < max_generation; generation++) {

			population->solve(problem);
/*
			std::cout << "printing population." << std::endl;
			std::cout << population->to_string() << std::endl;
*/
/*
			getchar();
*/
			best_entity = population->get_best_entity();

			// invoke call back indicating the generation and the best entity.
			on_evolution(generation, *best_entity);

			if (problem.get_min_score_requirement() <= best_entity->get_score() ) {
				solved = true;
				break;
			}

			Population * new_population = new Population(entity_meta);


			// Selection & Crossover
			for (int i=new_population->get_entity_count();
					 i<population->get_entity_count();
					 i++) {
				std::shared_ptr<Entity> e1 = population->select_dominant(domiant_candidate_count);
				std::shared_ptr<Entity> e2 = population->select_dominant(domiant_candidate_count);

				std::shared_ptr<Entity> new_entity( e1->crossover(*e2) );

				new_population->add_entity(new_entity);
//				std::cout << "Adding new entity to next generation : " << new_entity->to_string();
			}

			// Mutation
			new_population->mutate();

			// Demolish current population, make the eco-system to have the new population only.
			delete population;
			population = new_population;
		}

		if (solved) {
			return best_entity.get();
		}

		return NULL;
	}
private :
	bool keep_best_entity;
	int domiant_candidate_count;
	Population * population;
	const EntityMeta & entity_meta;
};

#endif /* ECOSYSTEM_H_ */
