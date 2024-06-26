nntrainer_inc = [
  include_directories('./include'),
  include_directories('../api')
]

# pc file is not present for 'ml-api-common' yet
if cxx.has_header('nnstreamer/ml-api-common.h', required: false)
  nntrainer_inc += include_directories ('/usr/include/nnstreamer')
else
  nntrainer_inc += include_directories ('../api/capi/include/platform')
endif

# Dependencies
nntrainer_base_deps=[
  openmp_dep,
  blas_dep,
  iniparser_dep,
  libm_dep,
  libdl_dep,
  thread_dep
]

if build_platform == 'tizen'
  nntrainer_base_deps += dependency('dlog')
endif

nntrainer_sources = [
  'src/activation_layer.cpp',
  'src/addition_layer.cpp',
  'src/bn_layer.cpp',
  'src/conv2d_layer.cpp',
  'src/databuffer.cpp',
  'src/databuffer_file.cpp',
  'src/databuffer_func.cpp',
  'src/fc_layer.cpp',
  'src/flatten_layer.cpp',
  'src/input_layer.cpp',
  'src/layer.cpp',
  'src/lazy_tensor.cpp',
  'src/loss_layer.cpp',
  'src/model_loader.cpp',
  'src/neuralnet.cpp',
  'src/nntrainer_logger.cpp',
  'src/optimizer.cpp',
  'src/parse_util.cpp',
  'src/pooling2d_layer.cpp',
  'src/tensor.cpp',
  'src/tensor_dim.cpp',
  'src/util_func.cpp',
  'src/blas_interface.cpp'
]

nntrainer_headers = [
  'include/activation_layer.h',
  'include/addition_layer.h',
  'include/bn_layer.h',
  'include/conv2d_layer.h',
  'include/databuffer.h',
  'include/databuffer_file.h',
  'include/databuffer_func.h',
  'include/fc_layer.h',
  'include/flatten_layer.h',
  'include/input_layer.h',
  'include/layer.h',
  'include/lazy_tensor.h',
  'include/loss_layer.h',
  'include/model_loader.h',
  'include/neuralnet.h',
  'include/nntrainer_log.h',
  'include/nntrainer_logger.h',
  'include/optimizer.h',
  'include/parse_util.h',
  'include/pooling2d_layer.h',
  'include/tensor.h',
  'include/tensor_dim.h',
  'include/util_func.h',
  'include/blas_interface.h',
  '../api/nntrainer-api-common.h'
]

# Build libraries
nntrainer_shared = shared_library('nntrainer',
  nntrainer_sources,
  dependencies: nntrainer_base_deps,
  include_directories: nntrainer_inc,
  install: true,
  install_dir: nntrainer_libdir
)

nntrainer_static = static_library('nntrainer',
  nntrainer_sources,
  dependencies: nntrainer_base_deps,
  include_directories: nntrainer_inc,
  install: true,
  install_dir: nntrainer_libdir
)

nntrainer_lib = nntrainer_shared
if get_option('default_library') == 'static'
  nntrainer_lib = nntrainer_static
endif

nntrainer_dep = declare_dependency(link_with: nntrainer_lib,
  dependencies: nntrainer_base_deps,
  include_directories: nntrainer_inc
)

# Install headers
install_headers(nntrainer_headers,
  subdir: 'nntrainer'
)
