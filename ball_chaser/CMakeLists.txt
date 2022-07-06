cmake_minimum_required(VERSION 3.0.2)
project(ball_chaser)


find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  DriveToTarget.srv
  
)
## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ball_chaser
#  CATKIN_DEPENDS messge_generation roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(drive_bot src/drive_bot.cpp)
target_link_libraries(drive_bot ${catkin_LIBRARIES})
add_dependencies(drive_bot ${${PROJECT_NAME}_EXPORTED_TARGETS}
#실행파일 빼고 같구만.
${catkin_EXPORTED_TARGETS})

add_executable(process_image src/process_image.cpp)
target_link_libraries(process_image ${catkin_LIBRARIES})
add_dependencies(process_image ${${PROJECT_NAME}_EXPORTED_TARGETS}
#실행파일 빼고 같구만.
${catkin_EXPORTED_TARGETS})



