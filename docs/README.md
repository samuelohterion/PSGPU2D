## Particle Simulator on GPU 2D
This is a framework for a particle simulator in 2d which only uses 1 texture to compute the physical behavior of many 2d particles. The call is always of type GL_POINTS. The primitives are created in the geometry shader.

### PSGPU2D

PSGPU is a lightweight and easy-to-use particles simulation system.

### Shaders

1. simulation
  - simu.vert
  - simu.geom
  - simu.frag

2. view
  - view.vert
  - view.geom
  - view.frag

3. post process (in future)
  - popr.vert
  - popr.geom
  - popr.frag
