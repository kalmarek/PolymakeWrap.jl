#include "polymake_includes.h"

#include "polymake_tools.h"

#include "polymake_functions.h"

#include "polymake_arrays.h"


void polymake_module_add_array(jlcxx::Module& polymake){

  polymake.add_type<jlcxx::Parametric<jlcxx::TypeVar<1>>>("pm_Array", jlcxx::julia_type("AbstractArray", "Base"))
    .apply<
      pm::Array<int32_t>,
      pm::Array<int64_t>
      // pm::Array<pm::Set<int32_t>>,
      // pm::Array<pm::Matrix<pm::Integer>>
    >([](auto wrapped){
      typedef typename decltype(wrapped)::type WrappedT;
      typedef typename decltype(wrapped)::type::value_type elemType;
      typedef typename jlcxx::ArrayRef<elemType>::iterator jlArrayIter;
      
      // wrapped.constructor<int32_t>();
      // wrapped.constructor<int32_t, elemType>();
      
      wrapped.template constructor<int64_t>();
      wrapped.template constructor<int64_t, elemType>();
      
      
      wrapped.method("_new_array", [](jlcxx::ArrayRef<elemType> A){
        pm::Array<elemType> a{(int32_t) A.size(), A.begin()};
        return a;
      });
      
      wrapped.method("_getindex", [](WrappedT& V, int64_t n){
        return elemType(V[n-1]);
      });
      wrapped.method("_setindex!",[](WrappedT& V, elemType v, int64_t n){
          V[n-1]=v;
          return v;
      });
      wrapped.method("length", &WrappedT::size);
      wrapped.method("resize!", [](WrappedT& A, int64_t newsz){
        A.resize(newsz);
      });
      
      wrapped.method("append!", [](WrappedT& A, WrappedT& B){
        A.append(B);
        return A;
      });
      // wrapped.method("append!", [](WrappedT& A, jlcxx::ArrayRef<elemType> B){
      //     A.append(B.size(), B.begin());
      //     return A;
      // });
      wrapped.method("fill!", [](WrappedT& A, elemType& x){
        A.fill(x);
        return A;
      });
      
      wrapped.method("show_small_obj", [](WrappedT& A){
        return show_small_object<WrappedT>(A);
      });
    });
}
