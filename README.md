
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
- [ ] rosPlan

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






# About the material's colors 

As also mentioned in the [robot_modelling][1] repo, it is possible to appreciate  [here][2] a Gazebo color palette with xckd color names, by @naoki_mizuno

### Resources 

[1]: https://github.com/fedehub/robot_modelling
[2]: https://gist.github.com/naoki-mizuno/5e63a13597d5c5fe817c1600b829595e#file-xkcd_colors-urdf-xacro-L1
