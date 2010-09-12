import glob

# create build environment
env = Environment()

# determine compiler and linker flags for SDL
env.ParseConfig('sdl-config --cflags')
env.ParseConfig('sdl-config --libs')

# gather a list of source files
SOURCES = glob.glob('*.c')

# add additional compiler flags
env.Append(CCFLAGS = ['-g', '-Wall', '-O3'])
#env.Append(LINKFLAGS = ['-pg'])
# add additional libraries to link against
#env.Append(LIBS = ['SDL_mixer', 'SDL_image'])
env.Append(LIBS = ["SDL_gfx"])

# build target
# output executable will be "game"
env.Program(target = 'layman', source = SOURCES)
