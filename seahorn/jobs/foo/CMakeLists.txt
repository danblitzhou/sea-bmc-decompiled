add_executable(foo
  ${FOO_ROOT}/decompiled.c
  ${FOO_ROOT}/orig.c
  foo_harness.c)

sea_attach_bc_link(foo)
