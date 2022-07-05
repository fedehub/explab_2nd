#! /bin/bash

clear
cd ./urdf
rosrun xacro xacro detectiBot.xacro --inorder > detectiBot.urdf
urdf_to_graphiz detectiBot.urdf
evince detectiBot.pdf
roslaunch robot_modelling model_viewer.launch