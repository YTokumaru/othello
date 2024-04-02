add_subdirectory(othello)
add_subdirectory(sample_library)
add_subdirectory(ftxui_sample)

if(othello_ENABLE_MPI)
  add_subdirectory(mpi_sample)
endif()
