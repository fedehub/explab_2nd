
#define NODE_NAME "action_interface"

#ifndef __DEBUG_MACROS__
#define __DEBUG_MACROS__

#define LOGSQUARE( str )  "[" << str << "] "
#define OUTLABEL          LOGSQUARE( NODE_NAME )
#define TLOG( msg )       ROS_INFO_STREAM( OUTLABEL << msg )
#define TWARN( msg )      ROS_WARN_STREAM( OUTLABEL << "WARNING: " << msg )
#define TERR( msg )       ROS_WARN_STREAM( OUTLABEL << "ERROR: " << msg )

#endif
#include "rosplan_action_interface/RPActionInterface.h"

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include "ros/ros.h"
#include "explab_2nd/Oracle.h"
#include <erl2/ErlOracle.h>
#include <erl2/Oracle.h>
#include "explab_2nd/Position.h"

#include <string>
#include <map>
#include <signal.h>


namespace KCL_rosplan {
	
class myaction : public RPActionInterface
{
public:
	
	// node constructor
	myaction() : RPActionInterface(  )
	{
		// init nodo

	}
	
	// action dispatch callback 
	bool concreteCallback ( const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		/*
		// action name
		std::cout << "action name: " << msg->name << std::endl;
		
		//params
		std::cout << "action params: " << std::endl;
		for( auto it = msg->parameters.begin() ; it != msg->parameters.end() ; ++it )
			std::cout << "param name:'" << it->key << "' value:'" << it->value << "'" << std::endl;
		*/

		if( class_initialized && ( msg->name == action_name ) )
		{
			// prendi il nome dell'azione
			// e scegli quale funzione avviare a seconda del nome
			if( action_name == "gather_hint" )
				return gather_hint_action();

			else if( action_name == "move_to_wp" )
				return move_to_wp_action( msg );

			else if( action_name == "shift_gripper")
				return shift_gripper_action();

			else if( action_name == "reach_temple")
				return reach_temple_action( msg );
			
			else if( action_name == "leave_temple")
				return leave_temple_action( msg );

			else if( action_name == "check_consistent_hypo")
				return check_consistent_hypo_action();

			else
				TERR("An error occoured while looking for any correspondance with the available actions ");
				return false;
		}
		else if (!class_initialized)
		{
			// istanzia le interfacce ROS a seconda del nome dell'azione
			if( msg->name == "gather_hint" )
				gather_hint_setup();

			else if( msg->name == "move_to_wp" )
				move_to_wp_setup(msg);

			else if(msg->name == "shift_gripper")
				shift_gripper_setup();

			else if(msg->name == "reach_temple")
				reach_temple_setup(msg);

			else if(msg->name == "leave_temple")
				leave_temple_setup(msg);

			else if(msg->name == "check_consistent_hypo")
				check_consistent_hypo_setup();

			else if(msg->name == "query_hypo")
				query_hypo_setup();
			else
				return false;
			
			class_initialized = true;
			action_name = msg->name;

			return true;
		}
		else
			return false; // gestisci meglio il caso d'errore 
	}

private: 

	ros::NodeHandle nh;
	
	// services

	ros::ServiceClient cl_go_to_point;

	// SETUP of single actions 

	bool class_initialized = false;

	std::string action_name = "";

	void gather_hint_setup()
	{
		// istanzia il subscriber con l'oracolo
		
	}

	void move_to_wp_setup( const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
		cl_go_to_point = nh.serviceClient<explab_2nd::Position>( "/go_to_point" );
	}

	void reach_temple_setup( const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
		cl_go_to_point = nh.serviceClient<explab_2nd::Position>( "/go_to_point" );
	}

	void leave_temple_setup( const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...

		// client a go_to_point
		cl_go_to_point = nh.serviceClient<explab_2nd::Position>( "/go_to_point" );
	}

	void check_consistent_hypo_setup()
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
	}

	void query_hypo_setup()
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
	}
	
	void shift_gripper_setup( )
	{
		// ...
	}




	// ACTIONS implementation

	bool gather_hint_action()
	{
		return true; // implementazione dell'azione
	}

	bool move_to_wp_action( const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		// chiama costruttore
		explab_2nd::Position mt;
		// trova il waypoint a cui andare 
		// dal waypoint ricava le coordinate 2D dove muovere il robot	
		if(msg->parameters[1].value == "wp1")
			{
				// set the goal coordinates
				mt.request.x = 2.5;
				mt.request.y = 0.0;
				mt.request.theta = -3.14/2;
			}
		// if the second parameter from the plan is wp2
		else if (msg->parameters[1].value == "wp2")
			{
				// set the goal coordinates
				mt.request.x = 0.0;
				mt.request.y = 2.5;
				mt.request.theta = 0.0;
			}
		// if the second parameter from the plan is wp3
		else if (msg->parameters[1].value == "wp3")
			{
				// set the goal coordinates
				mt.request.x = -2.5;
				mt.request.y = 0.0;
				mt.request.theta = 3.14/2;
			}
		// if the second parameter from the plan is wp4
		else if (msg->parameters[1].value == "wp4")
			{
				// set the goal coordinates
				mt.request.x = 0.0;
				mt.request.y = -2.5;
				mt.request.theta = 3.14;
			}

		// print some info messages 
		std::cout << "Leaving [" << msg->parameters[0].value << "] location for reaching [" << msg->parameters[1].value <<"] at: " << std::endl;
		std::cout << "x = (" << mt.request.x << ") ;y =  [" << mt.request.y <<") z = (" << mt.request.theta << ") " << std::endl;
		// service call to navigation service go_to_point 
		cl_go_to_point.call(mt);
		std::cout << "Position successfuly reached!" << std::endl; 
		
		return true; 
		
	}

	bool leave_temple_action( const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		// chiama costruttore
		explab_2nd::Position lt;
		// trova il waypoint a cui andare 
		// dal waypoint ricava le coordinate 2D dove muovere il robot	
		if(msg->parameters[1].value == "wp1")
			{
				// set the goal coordinates
				lt.request.x = 2.5;
				lt.request.y = 0.0;
				lt.request.theta = -3.14/2;
			}
		// if the second parameter from the plan is wp2
		else if (msg->parameters[1].value == "wp2")
			{
				// set the goal coordinates
				lt.request.x = 0.0;
				lt.request.y = 2.5;
				lt.request.theta = 0.0;
			}
		// if the second parameter from the plan is wp3
		else if (msg->parameters[1].value == "wp3")
			{
				// set the goal coordinates
				lt.request.x = -2.5;
				lt.request.y = 0.0;
				lt.request.theta = 3.14/2;
			}
		// if the second parameter from the plan is wp4
		else if (msg->parameters[1].value == "wp4")
			{
				// set the goal coordinates
				lt.request.x = 0.0;
				lt.request.y = -2.5;
				lt.request.theta = 3.14;
			}

		// print some info messages 
		std::cout << "Leaving [" << msg->parameters[0].value << "] location for reaching [" << msg->parameters[1].value <<"] at: " << std::endl;
		std::cout << "x = (" << lt.request.x << ") ;y =  [" << lt.request.y <<") z = (" << lt.request.theta << ") " << std::endl;
		// service call to navigation service go_to_point 
		cl_go_to_point.call(lt);
		std::cout << "Position successfuly reached!" << std::endl; 
		
		return true; 
	}

	bool reach_temple_action( const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		// chiama il servizio di navigazione verso (0,0)
		// chiama costruttore
		explab_2nd::Position rt;

		if(msg->parameters[1].value == "tp")
			{
				std::cout << " Populating the request for reaching temple coordinates" << std::endl;
				// set the goal coordinates
				rt.request.x = 0.0;
				rt.request.y = 0.0;
				rt.request.theta = 0.0;
			}
		else
		{
			std::cout << "ERROR while attempting to populate service request for reaching temple" << std::endl;
			return 1;
		}

		// print some info messages 
		std::cout << "Leaving [" << msg->parameters[0].value << "] location for reaching [" << msg->parameters[1].value <<"] at: " << std::endl;
		std::cout << "x = (" << rt.request.x << ") ;y =  [" << rt.request.y <<") z = (" << rt.request.theta << ") " << std::endl;
		// service call to navigation service go_to_point 
		cl_go_to_point.call(rt);
		std::cout << "Position successfuly reached!" << std::endl; 
		
		return true; 

	}

	bool check_consistent_hypo_action()
	{
		return true; // chiamata a servizio go_to_point
	}

	bool query_hypo_action()
	{
		return true; // chiamata a servizio go_to_point
	}
	
	bool shift_gripper_action()
	{
		return true; // chiamata a servizio go_to_point
	}



	void cbk_gather_hint( const erl2::ErlOracle::ConstPtr& hint )
	{
		// implementazione del subscriber ... 
	}
};

}


int main(int argc, char **argv) 
{
	ros::init(argc, argv, NODE_NAME, ros::init_options::AnonymousName);
	ros::NodeHandle nh("~");
	
	// create PDDL action publisher
	KCL_rosplan::myaction ac;
	
	// run the node
	ac.runActionInterface();
	
	return 0;
}
