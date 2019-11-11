#include "polymake_includes.h"

#include "polymake_direct_calls.h"

auto low_level_solve_LP(
    pm::Matrix<pm::Rational> inequalities,
    pm::Matrix<pm::Rational> equalities,
    pm::Vector<pm::Rational> objective,
    bool                     maximize)
{
    auto solution = polymake::polytope::solve_LP<pm::Rational,
    pm::Matrix<pm::Rational>, pm::Matrix<pm::Rational>, pm::Vector<pm::Rational>>
    (inequalities, equalities, objective, maximize);
    return solution.solution;
}

void polymake_module_add_direct_calls(jlcxx::Module& polymake)
{
    polymake.method("low_level_solve_LP", &low_level_solve_LP);
    // polymake.method("low_level_solve_LP_direct", &polymake::polytope::solve_LP<pm::Rational, pm::Matrix<pm::Rational>, pm::Vector<pm::Rational>>);
}
