/*
 * Problem.h
 *
 *  Created on: 2013. 9. 18.
 *      Author: ilvsusie
 */

#ifndef PROBLEM_H_
#define PROBLEM_H_

#include <vector>
#include "Entity.h"


class Problem {
public:
	Problem(int number_of_genes, int * a_problem_genes, int a_min_score_requirement) {
		for (int i=0; i<number_of_genes; i++) {
			problem_genes[i] = a_problem_genes[i];
		}
		min_score_requirement = a_min_score_requirement;
	}

	virtual ~Problem() {

	}

	int get_min_score_requirement() const {
		return min_score_requirement;
	}

	int get_worst_gene_diffs(const EntityMeta & entity_meta) const {
		int worst_diffs = 0;
		for (int i=0; i< entity_meta.get_gene_count(); i++) {
			worst_diffs += entity_meta.get_gene_fence_value(i);
		}
		return worst_diffs;
	}

	/*! Solve the problem based on the genes in a given entity, return the evaluation score.
	 */
	int get_evaluation_score(const Entity & entity) const {
		const EntityMeta & entity_meta = entity.get_entity_meta();
		int worst_diffs = get_worst_gene_diffs(entity_meta);

		int total_diffs = 0;
		for (int i=0; i< entity_meta.get_gene_count(); i++) {
			int gene_diff = problem_genes[i] - entity.get_gene(i);
			total_diffs += Util::abs(gene_diff);
		}

		return worst_diffs - total_diffs;
	}

private :
	int min_score_requirement;
	std::vector<int> problem_genes;
};

#endif /* PROBLEM_H_ */
