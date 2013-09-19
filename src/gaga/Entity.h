/*
 * Entity.h
 *
 *  Created on: 2013. 9. 18.
 *      Author: ilvsusie
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <sstream>
#include "Problem.h"
#include "Util.h"
#include "Config.h"

class EntityMeta {
public :
	EntityMeta(int a_gene_count, int * a_gene_fence_values) {
		for (int i=0; i<a_gene_count; i++) {
			gene_fence_values[i] = a_gene_fence_values[i];
		}
	}

	virtual ~EntityMeta() {
	}

	int get_gene_count() const {
		return gene_fence_values.size();
	}
	int get_gene_fence_value(int gene_index) const {
		return gene_fence_values[gene_index];
	}
private:
	/*! Keep the fence value that a gene can have. A gene at an index can have values less than the fence value at the index.
	 */
	std::vector<int> gene_fence_values;
};

class Entity {
public:
	Entity(const EntityMeta & a_entity_meta) : entity_meta(a_entity_meta){
	}

	virtual ~Entity() {

	}

	void randomize() {
		int gene_count = entity_meta.get_gene_count();
		genes.resize( gene_count );
		for (int i=0; i<gene_count; i++) {
			randomize_gene(i);
		}
	}

	/*! Pick a random value for a gene at index.
	 *
	 */
	void randomize_gene(int index) {
		genes[index] = entity_meta.get_gene_fence_value(index) * Util::random();
	}

	/*! Return the evaluation score, after solving the problem recently.
	 */
	int get_score() const {
		return score;
	}

	void set_score(int a_score) {
		score = a_score;
	}

	/*!
	 * Randomly mutate genes, based on MUTATION_PROBABILITY.
	 */
	void mutate() {
		int gene_count = entity_meta.get_gene_count();
		for (int i=0; i<gene_count; i++) {
			if (Util::random() <= GAGA_MUTATION_PROBABILITY) {
				randomize_gene(i);
			}
		}
	}

	Entity * crossover(const Entity & another_entity) const {
		Entity * new_entity = new Entity(entity_meta);

		int gene_count = entity_meta.get_gene_count();
		for (int i=0; i<gene_count; i++) {
			int selected_gene_value;
			if ( Util::random() <= GAGA_GENE_SELECTION_PROBABILITY) {
				selected_gene_value = this->get_gene(i);
			} else {
				selected_gene_value = another_entity.get_gene(i);
			}
			new_entity->set_gene( i, selected_gene_value );
		}

		return new_entity;
	}

	std::string to_string() const {
		std::stringstream strstream;

		strstream << "[";

		for ( size_t i=0; i<genes.size(); i++) {
			strstream << genes[i] << " ";
		}
		strstream << "]";

		return strstream.str();
	}

	int get_gene(int index) const {
		return genes[index];
	}

	void set_gene(int index, int value) {
		genes[index] = value;
	}

	const EntityMeta & get_entity_meta() const {
		return entity_meta;
	}

private :
	const EntityMeta & entity_meta;
	std::vector<int> genes;
	int score;
};

#endif /* ENTITY_H_ */
