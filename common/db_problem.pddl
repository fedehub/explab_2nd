(define (problem task)
(:domain db_domain)
(:objects
    wp1 - waypoint 
    wp2 - waypoint 
    wp3 - waypoint 
    wp4 - waypoint
    tp -  temple
)
(:init



    (at_temple tp)
	(not_gripper_inplace)

)
(:goal (and
    (true_hypo)
))
)
