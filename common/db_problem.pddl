(define (problem task)
(:domain db_domain)
(:objects
    detectiBot - robot
    hp - hypo 
    wp1 wp2 wp3 wp4 - waypoint
    
)
(:init
    (not ( gathered_hint wp1))
    (not ( gathered_hint wp2))
    (not ( gathered_hint wp3))
    (not ( gathered_hint wp4))

    (not ( complete_hypo))

    (not_gripper_in_place)
)
(:goal 
    (true_hypo)
)
)
