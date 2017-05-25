# GameMaker
This is a partial rewrite of the EnterpriseEngine in C++. Hopes that it will be slimmer, and more effecient. In addition, the engine will also support skeletal animation, and physically based rendering (pbr) that the EnterpriseEngine did not.

## General TODOs
- Need a good logging library, shouldn't be using `cout` so often
- Should I be using a namespace?
- Improve Shader SetUniform() function, shouldn't be five different ones
- Use quaternions with the cams instead of euler rotation

## Lighting Thoughts
There should be the option to generate FBOs to be used as environment maps for PBR textures at runetime, or the option to use the skybox. This way both indoor and outdoor scenes can be supported for physically real reflections.