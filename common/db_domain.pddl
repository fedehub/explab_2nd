(define (domain db_domain)

	(:requirements 
			:strips 
			:typing 
			:fluents
			:durative-actions  
			:adl
			:disjunctive-preconditions 
	)

	(:types 
		waypoint
		robot
		hypo
		temple
	)

	(:predicates
		(at ?wp - waypoint) ;; robot at a certain place
		(has_been_at ?pl)   ;; robot has been at some place
		(not_yet_at ?pl)    ;; robot has not been at some place
		(true_hypo)         ;; true hypothesis, the real goal of the robot
		(completed_hypo)    ;; completed hypothesis, hence consistent 
		(gathered_hint)     ;; the hint that has been collectd 
		(gripper_inplace)   ;; ... is correctly positioned for gathering hints ...
		(not_gripper_inplace)    ;; ... is not correctly positioned ...
		(at_temple ?tp - temple) ;; robot is in temple, ready for querying
	)

	;; init phase, needed for starting from scratch each turn 

	(:durative-action init_phase

		:parameters (?wp1 ?wp2 ?wp3 ?wp4 - waypoint 
				?tp - temple 
				?rb - robot )

		:duration (= ?duration 60)

		:condition (and
			(at start(at ?wp1))
			(at start(has_been_at ?wp1))
			(at start(has_been_at ?wp2 ))
			(at start(has_been_at ?wp3))
			(at start(has_been_at ?wp4))
			(at start(has_been_at ?tp))
			)

		:effect (and
			(at end(not(has_been_at ?wp2) ))
			(at end(not(has_been_at ?wp3) ))
			(at end(not(has_been_at ?wp4) ))
			(at end(not(not_yet_at  ?wp2) ))
			(at end(not(not_yet_at  ?wp3) ))
			(at end(not(not_yet_at  ?wp4) ))
			)
	)

	;; move to any waypoint

	(:durative-action go_to_wp

		:parameters (?from ?to - waypoint )

		:duration( = ?duration 60)

		:condition (and
			(at start(at ?from))
			(at start(not_gripper_inplace))
			(at start(not_yet_at ?to ))
			)

		:effect (and
			(at end(at ?to))
			(at end(has_been_at ?from))
			(at end(not(not_yet_at ?to)))
			(at end(not (at ?from )))
			)
	)

	;; move gripper
	(:durative-action shift_gripper

		:parameters (?from - waypoint
				?tp - temple)

		:duration( = ?duration 60)

		:condition (and
			(at start(at ?from))
			(at start(has been at ?from))
			(at start(not_gripper_inplace))
			(at start(not(at_temple ?tp)))
			)
			

		:effect (and
			(at end(not(not_gripper_inplace)))
			(at end(gripper_inplace))
			)
	)		

	;; collect the hint within the marker 
	(:durative-action gather_hint

		:parameters (?wp - waypoint ?rb - robot temple - ?tp )

		:duration ( = ?duration 15)

		:condition (and 
			(at start(at ?wp ))
			(at start(gripper_inplace))
			(at start(has_been_at ?wp))
			(at start(not(at_temple ?tp)))        
			)

		:effect (and 
			(at end( gathered_hint ))
			(at start(not(gripper_inplace)))
			(at start( not_gripper_inplace))
			)
	)


	;; checking with ontology wheter an hypo is complete or not 
	(:durative-action check_completed_hypo

		:parameters(?rb - robot  ?wp - waypoint )

		:duration (= ?duration 60)

		:condition (and 
				(at start( at(?wp - waypoint))) 
				(at start( gathered_hint ))
				)
				
		:effect ( and
				(at end (completed_hypo))
				(at start(not (gathered_hint)))
				)
	)	



	;; reach the temple for asking oracle 		
	(:durative-action reach_temple

		:parameters ( ?from - waypoint  ?rb - robot ?tp - temple )

		:duration   ( = ?duration 60)

		:condition  (and
				(at start(at ?from))
				(at start(completed_hypo))
				)

		:effect (and
			(at start(not (at ?from )))
			(at end (at_temple ?tp))
			)
	)


			
	;; query the oracle for verifying whether an hypo is the true one or not
	(:durative-action query_hypo

		:parameters (?tp - temple)

		:duration   (= ?duration 60)

		:condition (and 
				(at start(at_temple ?tp))
				(at start(completed_hypo))
				)
					
		:effect (and
				(at end(true_hypo))
				)
	)		
			


	;; leave the temple for starting to explore 
	(:durative-action leave_temple

		:parameters (?from - temple ?to - waypoint )

		:duration (= ?duration 60)

		:condition(and
			(at start (at_temple ?from))
			)

		:effect(and
			(at start (not(at_temple ?from)))
			(at end(at ?to ))
			)
	)

)			




