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
	(at ?wp - waypoint ?rb - robot)
	(true_hypo     ?hp - hypo)
	(complete_hypo ?hp - hypo)
	(gathered_hint ?wp - waypoint)
    (not_gripper_in_place)
)


;; move to wp
(:durative-action go_to_wp

	:parameters (?from ?to - waypoint
                 ?rb - robot
                )

	:duration ( = ?duration 15)

	:condition (and
		(at start(at ?from ?rb))
        (at start(not_gripper_in_place))
		)

	:effect (and
		(at end(at ?to ?rb))
		(at start (not (at ?from ?rb))))
		)

;; reach the temple for asking oracle 		
(:durative-action reach_temple

	:parameters ( ?from - waypoint 
                  ?to - temple 
                  ?rb - robot
                )

	:duration ( = ?duration 15)

	:condition (at start(at ?from ?rb))

	:effect (and
		(at start(not (at ?from ?rb)))
		(at end (at_temple ?to ?rb))
		)
)

;; leave the temple for starting to explore 
(:durative-action leave_temple

	:parameters ( ?from - temple 
                  ?to - waypoint
                  ?rb - robot
                )

	:duration ( = ?duration 15)

	:condition(and
				(at start (at_temple ?from ?rb))
				)

	:effect(and
		(at start (not(at_temple ?from ?rb)))
		(at end(at ?to ?rb))
		)
)

;; collect the hint within the marker 
(:durative-action gathered_hint

	:parameters (?wp - waypoint
                 ?rb - robot 
                 ?hp - hypo
                )

	:duration ( = ?duration 15)

	:condition (and 
                    (at start(at ?wp ?rb ))
                    (at start(not_gripper_in_place))        
                )

	:effect (and 
				(at end( gathered_hint ?wp ?rb))
                (at end (not(not_gripper_in_place)))
			)
)


;; checking with ontology wheter an hypo is complete or not 
(:durative-action complete_hypo

	:parameters(?h - temple)

	:duration ( = ?duration 15)

	:condition (and 
				(at start (forall (?wp - waypoint) ( gathered_hint ?wp)))
				)
	:effect ( and
			(at end (complete_hypo))
			)
)			

;; query the oracle for verifying whether an hypo is the true one or not
(:durative-action query_hypo

	:parameters(?h - temple
                ?rb - robot 
                )

	:duration ( = ?duration 60)

	:condition (and 
				(at start(at_temple ?h ?rb))
				(at start(complete_hypo))
				)
				
	:effect (and
			(at end(true_hypo))
			)
)

)
