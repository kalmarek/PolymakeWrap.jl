for (m, flag) in [(:min, false), (:max, true)]
    @eval begin
        function low_levl_solve_LP(
            inequalities::AbstractMatrix,
            equalities::AbstractMatrix,
            objective::AbstractVector, ::typeof($m))

            return Polymake.low_level_solve_LP(
                convert(pm_Matrix{pm_Rational}, inequalities),
                convert(pm_Matrix{pm_Rational}, equalities),
                convert(pm_Vector{pm_Rational}, objective),
                $flag
            )
        end
    end
end

solve_LP(inequalities, objective; sense=max) = low_levl_solve_LP(inequalities, pm_Matrix{pm_Rational}(), objective, sense)

solve_LP(inequalities, equalities, objective; sense=max) = low_levl_solve_LP(inequalities, equalities, objective, sense)
