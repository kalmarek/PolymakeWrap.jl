#include "polymake_includes.h"

#include "polymake_tools.h"

#include "polymake_functions.h"

#include "polymake_incidencematrix.h"


void polymake_module_add_incidencematrix(jlcxx::Module& polymake)
{

    polymake
        .add_type<jlcxx::Parametric<jlcxx::TypeVar<1>>>(
            "pm_IncidenceMatrix", jlcxx::julia_type("AbstractMatrix", "Base"))
        .apply<pm::Symmetric, pm::NonSymmetric>([](auto wrapped) {
            typedef typename decltype(wrapped)::type             WrappedT;
            typedef typename decltype(wrapped)::type::value_type elemType;

            wrapped.template constructor<int32_t, int32_t>();
            // all* initializations are rowwise!

            wrapped.method("_getindex",
            [](const WrappedT& A, int64_t i, int64_t j) {
                return A(static_cast<long>(i) - 1, static_cast<long>(j) - 1);
            });

            wrapped.method("_setindex!",
                           [](WrappedT& A, const elemType& val, int64_t n) {
                               A[static_cast<long>(n) - 1] = val;
                           });

            wrapped.method("length", &WrappedT::size);
            wrapped.method("resize!", [](WrappedT& A, int64_t m, int64_t n) {
                A.resize(static_cast<long>(m), static_cast<long>(n));
                return A;
            });
            wrapped.method("empty!", [](WrappedT& A) {
                A.clear();
                return A;
            });
            wrapped.method("dropzero_rows!", [](WrappedT& A) {
                A.squeeze_rows();
                return A;
            });
            wrapped.method("dropzero_cols!", [](WrappedT& A) {
                A.squeeze_cols();
                return A;
            });


            wrapped.method("append!", [](WrappedT& A, WrappedT& B) {
                A.append(B);
                return A;
            });
            wrapped.method("fill!", [](WrappedT& A, const elemType& x) {
                A.fill(x);
                return A;
            });
            wrapped.method("show_small_obj", [](const WrappedT& A) {
                return show_small_object<WrappedT>(A);
            });
            wrapped.method("take",
                           [](pm::perl::Object p, const std::string& s,
                              WrappedT& A) { p.take(s) << A; });
        })

    polymake.method("to_incidence_matrix", [](const pm::perl::PropertyValue& pv) {
        return to_SmallObject<pm::IncidenceMatrix>(pv);
    });
}
