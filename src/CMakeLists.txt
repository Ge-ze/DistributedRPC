
aux_source_directory(. SRC_LIST)
add_library(rpc ${SRC_LIST})
target_link_libraries(rpc muduo_net muduo_base pthread zookeeper_mt)