/*
 * Population.h
 *
 *  Created on: 2013. 9. 18.
 *      Author: ilvsusie
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include <assert.h>
#include <map>
#include <memory>
#include "Entity.h"


class Population {
public:
	Population(const EntityMeta & a_entity_meta) : entity_meta( a_entity_meta ) {
	}
	virtual ~Population() {

	}

	void solve(const Problem & problem) {
		for (auto e : entities) {
			int score = problem.get_evaluation_score(*e);
			e->set_score(score);
		}
	}

	void populate(int population) {
		for (int i=0; i<population; i++) {
			std::shared_ptr<Entity> e = std::shared_ptr<Entity>( new Entity( entity_meta ) ) ;
			e->randomize();
			entities.push_back(e);
		}
	}

	void mutate() {
		for (auto e : entities) {
			e->mutate();
		}
	}

	/*! Return the entity with highest evaluation score.
	 */
	std::shared_ptr<Entity> get_best_entity() const {
		int max_score = -1;
		std::shared_ptr<Entity> best_entity;
		for (auto e : entities) {
			int score = e->get_score();
			if ( score > max_score ) {
				max_score = score;
				best_entity = e;
			}
		}
		return best_entity;
	}

	std::shared_ptr<Entity> select_dominant(int domiant_candidate_count) const {
		Population p(entity_meta);
		for (int i=0; i<domiant_candidate_count; i++) {
			int entity_index = (int) (Util::random() * entities.size());

			assert( entity_index >= 0 );
			assert( (size_t)entity_index < entities.size());

			p.add_entity( entities[i] );
		}

		return p.get_best_entity();
	}

	void add_entity(std::shared_ptr<Entity> e) {
		entities.push_back(e);
	}

	int get_entity_count() const {
		return entities.size();
	}

private :
	const EntityMeta & entity_meta;

	// list of entities
	std::vector<std::shared_ptr<Entity>> entities;

};

#endif /* POPULATION_H_ */
