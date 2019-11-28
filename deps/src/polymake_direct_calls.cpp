#include "polymake_includes.h"

#include "polymake_direct_calls.h"

auto direct_call_solve_LP(
    const pm::Matrix<pm::Rational>& inequalities,
    const pm::Matrix<pm::Rational>& equalities,
    const pm::Vector<pm::Rational>& objective,
    bool                            maximize)
{
    auto solution = polymake::polytope::solve_LP(inequalities, equalities, objective, maximize);
    return solution.solution;
}

auto direct_call_solve_LP_float(
    const pm::Matrix<double>& inequalities,
    const pm::Matrix<double>& equalities,
    const pm::Vector<double>& objective,
    bool                      maximize)
{
    auto solution = polymake::polytope::solve_LP(inequalities, equalities, objective, maximize);
    return solution.solution;
}


void polymake_module_add_direct_calls(jlcxx::Module& polymake)
{
    polymake.method("direct_call_solve_LP", &direct_call_solve_LP);
    polymake.method("direct_call_solve_LP_float", &direct_call_solve_LP_float);
    // polymake.method("low_level_solve_LP_direct", &polymake::polytope::solve_LP<pm::Rational, pm::Matrix<pm::Rational>, pm::Vector<pm::Rational>>);
}
