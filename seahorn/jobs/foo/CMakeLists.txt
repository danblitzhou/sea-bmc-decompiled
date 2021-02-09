add_executable(foo
  ${FOO_ROOT}/decompiled.c
  ${FOO_ROOT}/orig.c
  foo_harness.c)
configure_file(sea.yaml sea.yaml @ONLY)
sea_attach_bc_link(foo)
