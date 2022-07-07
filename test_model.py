#! /bin/bash

clear
cd ./urdf
rosrun xacro xacro detectiBot.xacro --inorder > detectiBot.urdf
urdf_to_graphiz detectiBot.urdf
evince detectiBot.pdf
roslaunch explab_2nd model_viewer.launch
