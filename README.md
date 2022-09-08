
<img align="left" width="80" height="80" src="https://github.com/fedehub.png" alt="github icon">
<h1> Experimental Robotics Laboratory - 2nd assignment  </h1>

Implementation of the second assignment of the exprob course 

# 🚀 Roadmap

To do:

- [x] develop (or update) the robot model
  - [x] robot description: explore a bit the URDF 🌍 
    - [x] create a new repo for testing ([click here!][1])
  - [x] add xacro file for materials 
  - [x] add ros controllers 
  - [x] Plugins for ros controllers? 
  - [x] add transmission 
  - [x] add in a `config` folder the `motors_config.yaml` file
  - [x] modify the `launch` file, accordingly
- [x] moveit frammework
- [x] output file 

# About the robot 

The robot model employed for this assigment can be found in the urdf folder under both file extensions  `.xacro` and `.urdf`. Please note that this is a mere reinterpretation of the robot model explained during the course 

Here below an image representing the overall structure of the **detectiBot** model

<p align = center>
<img src="https://user-images.githubusercontent.com/61761835/178159762-7e1748ca-54a3-4912-a540-6a391b6beb55.png" width="500" height="500">
</p>

> ⚠️ _Remark: this is the same model used for configuring the mvoeit package!_

### checking the model: step by step

For cheking the model:

1. save the current model with `.urdf` extension
2. check if the current model contains errors (by parsing the urdf tag and show the potentially occuring error)

   ```sh
   check_urdf detectiBot.urdf
   ```

3. for viewing the structure of the robot links and joints graphically (two files will be generated with both `.gv` and `.pdf` extensions)

    ```sh
    urdf_to_graphiz detectiBot.urdf
    ```

4. For inspecting the model:
   
    ```sh
    evince detectiBot.pdf
    ```

### from xacro to urdf 

For ending up with a ".urdf" version of our .xacro file, simply run: 

```sh
rosrun xacro xacro ???.xacro --inorder > ???.urdf

```

where `???` simply stands for the name of the file 
    
### checking the model: in a wink …

For checking the model, and launch the simulation:

1. enable "execution" permission

    ```sh
    chmod +x test_model.py
    ```
  
3. run the script

    ```sh
    ./test_model.py 
    ```

### using Rviz 

For taking a look at the robot structure by means of RVIZ, please run:

```sh
roslaunch explab_2nd_moveit demo.launch
```

this is a gif demonstrating the `demo.launch` usage

![moveit_demo](https://user-images.githubusercontent.com/61761835/178219740-f194c2bb-8181-4839-aeaa-b59f9abc5982.gif)



## MoveIt! Setup Assistant

The MoveIt Setup Assistant is a graphical user interface for configuring any robot for use with MoveIt. It mainly generates:
* a Semantic Robot Description Format (SRDF) file for a robot.
* other necessary configuration files for use with the MoveIt pipeline. 
For the complete explanation about a proper package configuration, please refer to [setup_assistant_tutorial][3]


For launching the MoveIt Setup Assistant, install it and run:

```sh
roslaunch moveit_setup_assistant setup_assistant.launch
```

> ⚠️ Please note that for this  assignment a specific version of MoveIt! has been selected. For more info, please refer to my repo ([here][4])

Although MoveIt! has tried to streamline the Gazebo integration, the auto-generated launch and config files are not readily available to use. Indeed, intervening and configuring some parameters and files was needed. For doing so, it is suggestable to refer to [this useful guide][5]. 

In this specific case, it was sufficient to:

1. comment a line (21) of the `trajectory_execution.launch.xml` file, inside the launch folder 

  ```xml
  <!-- <arg name="execution_type" value="$(arg execution_type)" /> -->
  ```

2. modify the "default" values chosen for the PID controllers and the `i_clamp`, within the `ros_controllers.yaml` file; 

  ```yaml
  # for all arm_joint
    p: 10
    d: 0
    i: 0
    i_clamp: 0
   ```
3. add to the nineth line of `ros_controllers.launch` file, `joint_state_controller` as args, before `arm_controller`

  ```yaml
    <!-- Load the controllers -->
    <node name="controller_spawner" pkg="controller_manager" type="spawner"   respawn="false"
    output="screen" args="joint_state_controller arm_controller "/>

  ```

4. modify the default velocity and acceleration's factors, in the `joint_limits.yaml` configuration file 

  ```yaml
  default_velocity_scaling_factor: 1
  default_acceleration_scaling_factor: 1
  
  ```

Then, for testing the gazebo integration, please run

```sh
roslaunch explab_2nd_moveit demo_gazebo.launch 

```

For a glimpse of how it works

![demo_gaz](https://user-images.githubusercontent.com/61761835/178574333-083abf9a-4592-4a64-a238-3871448d5675.gif)






## About the material's colors 

As also mentioned in the [robot_modelling][1] repo, it is possible to appreciate  [here][2] a Gazebo color palette with xckd color names, by @naoki_mizuno




<!-- References -->

[1]: https://github.com/fedehub/robot_modelling
[2]: https://gist.github.com/naoki-mizuno/5e63a13597d5c5fe817c1600b829595e#file-xkcd_colors-urdf-xacro-L1
[3]: https://ros-planning.github.io/moveit_tutorials/doc/setup_assistant/setup_assistant_tutorial.html
[4]: https://github.com/fedehub/robot_modelling#some-remarks
[5]: https://medium.com/@tahsincankose/custom-manipulator-simulation-in-gazebo-and-motion-planning-with-moveit-c017eef1ea90 
