(define (problem task)
(:domain db_domain)
(:objects
    wp1 wp2 wp3 wp4 - waypoint
    detectibot - robot
    tp - temple
)
(:init







    (not_gripper_inplace)

    (at_temple tp)


)
(:goal (and
    (true_hypo)
))
)
