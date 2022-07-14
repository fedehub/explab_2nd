(define (problem task)
(:domain db_domain)
(:objects
    detectiBot - robot
    wp1 wp2 wp3 wp4 - waypoint
    t0 - temple
)
(:init
    (not (gathered_hint wp1))
    (not (gathered_hint wp2))
    (not (gathered_hint wp3))
    (not (gathered_hint wp4))
    (not_yet_at wp1)
    (not_yet_at wp2)
    (not_yet_at wp3)
    (not_yet_at wp4)
    (at_temple t0)
    (not_gripper_inplace)
    (not (completed_hypo))
)

(:goal 
    (true_hypo)
)

)
