//
// Created by Alan Freitas on 2019-11-21.
//

#ifndef SCISTATS_BAYESIAN_THEOREM_H
#define SCISTATS_BAYESIAN_THEOREM_H

#include <scistats/common/concepts.h>

namespace scistats {

    /// \brief Calculates the posterior probability of an event given some
    /// evidence Calculates P(H|E) = (P(E|H)*P(H))/P(E) = P(E and B)/P(B) \note
    /// The prior is one's belief before evidence into account or prior
    ///       knowledge about the proposition.
    /// \note Any Bayes decision rule obtained by taking a proper prior over the
    ///       whole parameter space must be admissible.
    /// \note The model evidence (or marginal likelihood) considers all
    /// hypotheses Thus, it does not determine the relative probabilities of
    /// hypotheses. There are a few options to calculate the model evidence:
    /// - Law of total probability:
    ///   If there are there are n outcomes A1,A2,...,An, P(B) =
    ///   sum(P(B|Ai)P(Ai))
    /// - If there are infinite outcomes Ai, we need to integrate over all
    /// outcomes
    /// - If P(B) is too difficult to calculate,
    ///   - we ignore P(B) as the result will still be proportional to the
    ///   numerator
    ///   - we use monte carlo methods or variational Bayesian methods
    /// \note P(E|H)/P(E) (from P(E|H)*P(H)/P(E)) is the impact of E on H
    /// \tparam T Type of floating number
    /// \param likelyhood P(E|H): how much this evidence would support the
    /// hypothesis \param prior P(H): prior probability of the hypothesis \param
    /// model_evidence P(E): Probability of this evidence all hypotheses
    /// considered \return Posterior probability P(H|E) \see
    /// https://en.wikipedia.org/wiki/Bayesian_inference \see
    /// https://en.wikipedia.org/wiki/Jeffreys_prior \see
    /// https://en.wikipedia.org/wiki/Bayesian_network \see
    /// https://en.wikipedia.org/wiki/Markov_chain_Monte_Carlo \see
    /// https://en.wikipedia.org/wiki/Metropolis–Hastings_algorithm \see
    /// https://en.wikipedia.org/wiki/Bayesian_hierarchical_modeling \see
    /// https://en.wikipedia.org/wiki/Variational_Bayesian_methods \see
    /// https://www.quantstart.com/articles/Bayesian-Statistics-A-Beginners-Guide
    template <Floating T>
    T bayes_theorem(T likelyhood, T prior, T model_evidence) {
        return (likelyhood * prior) / model_evidence;
    }

    /// \brief The ratio of the probability of a hypothesis against other
    /// hypothesis P(E | H)/P(E | not H) This represents the amount of
    /// information we learned about a hypothesis If we ignore the
    /// model_evidence in our bayes theorem, the bayes factor should still be
    /// the same. This means how much our hypothesis is more likely after the
    /// evidence.
    template <Floating T>
    T bayes_factor(T evidence_given_h, T evidence_given_not_h) {
        return evidence_given_h / evidence_given_not_h;
    }

    /// \brief The ratio of the probability of a hypothesis against other
    /// hypotheses This ratio does not depend on the model evidence and prior
    /// beliefs: Ratio of 2 bayes theorems: P(H) * P(E | H) / P(E) / P(not H) *
    /// P(E | not H) / P(E)
    ///     : P(H) * P(E | H) / P(not H) * P(E | not H)
    ///     : P(E | H)/P(E | not H)
    /// Prior: P(H)/P(not H)
    /// Likelihood ration:  P(E | H) / P(E | not H)
    /// Posterior odds:  P(H | E) / P(not H | E)
    /// This represents the amount of information we learned about a hypothesis
    /// If we ignore the model_evidence in our bayes theorem, the bayes factor
    /// should still be the same. This means how much our hypothesis is more
    /// likely after the evidence. \tparam T Floating number \param p_h0
    /// Hypothesis probability: P(H) \param p_h1 Alternative hypothesis
    /// probability: P(not H) or P(H1) \param p_E_H0 Likelihood of evidence
    /// given hypothesis: P(E | H) \param p_E_H1 Likelihood of evidence given
    /// alternative hypothesis: P(E | not H) or P(E|H1) \return P(H | E) / P(not
    /// H | E)
    template <Floating T>
    T bayes_factor(T p_h0, T p_h1, T p_E_H0, T p_E_H1) {
        return (p_h0 * p_E_H0) / (p_h1 * p_E_H1);
    }

    /// \brief Bayes inference on continuous distributions
    /// \param PDF(theta): prior hypothesis about probability distribution of
    /// our random variable theta \param f(E|theta): likelihood of our evidence
    /// given our prior distribution hypothesis \param f(E): normalization /
    /// marginal likelihood of our evidence in any case \return P(theta|E):
    /// posterior probability distribution given our evidence \see
    /// https://www.youtube.com/watch?v=51bLRF02b4w \see
    /// https://www.countbayesie.com/blog/2015/4/25/bayesian-ab-testing \see
    /// https://www.countbayesie.com/blog/2016/5/1/a-guide-to-bayesian-statistics
    /// \see
    /// https://www.quantstart.com/articles/Bayesian-Statistics-A-Beginners-Guide

} // namespace scistats

#endif // SCISTATS_BAYESIAN_THEOREM_H
