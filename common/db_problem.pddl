(define (problem task)
(:domain db_domain)
(:objects
	detectiBot - robot
	wp1 - waypoint
	wp2 - waypoint
	wp3 - waypoint
	wp4 - waypoint	
	tp - temple
)

(:init
	
	(not_gripper_inplace)
	(at_temple tp)
)


(:goal 
	(true_hypo)
)


;; end problem
)
