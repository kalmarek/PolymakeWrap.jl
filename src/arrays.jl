import PolymakeWrap.Polymake.pm_Array

### convert TO polymake object

pm_Array(v::Vector{T}) where T = Polymake._new_array(v)
pm_Array{T}(v::Vector) where T = pm_Array(Vector{T}(v))

Base.size(a::pm_Array) = (length(a),)
