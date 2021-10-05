cmake_minimum_required (VERSION 3.5.1)
project (new_task_manage)

add_executable(new_task_manage main_module.c queue.c pack_handle.c pack_send.c task_queue.c task_test.c task_manage.c video_venc.c audio_venc.c video_queue.c audio_queue.c)
target_link_libraries(new_task_manage
    PRIVATE pthread
)




