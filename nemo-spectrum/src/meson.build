nemo_spectrum_sources = [
    'nemo-spectrum.c',
]

libnemo_spectrum = shared_library('nemo-spectrum',
    nemo_spectrum_sources,
    include_directories: rootInclude,
    dependencies: [
        libnemo,
    ],

    install: true,
    install_dir: libnemo_extension_dir,
)
