project('icons')
inkscape = find_program('inkscape')
svgo = find_program('svgo', required : false)

inkscape_env = {
  'DBUS_SESSION_BUS_ADDRESS': '',
  'XDG_RUNTIME_DIR': '/tmp',
}

names = ['logo', 'logo-white']

# Making Raw Svg (non-optimized)
sources = []
foreach name : names
  sources += files('source/' + name + '.svg')
endforeach

raw_svgs = []
foreach i : range(0, names.length())
  raw_svgs += custom_target(
    'svg-raw-' + names[i],
    input : sources[i],
    output : names[i] + '-R.svg',
    command : [
      inkscape,
      '@INPUT@',
      '--export-type=svg',
      '--export-area-drawing',
      '--actions=select-all;object-to-path;export-do',
      '--export-filename=@OUTPUT@',
    ],
    build_by_default : true
  )
endforeach

# If 'svgo' found, then optimizing SVGs
if svgo.found()
  # Making Optimized Svg
  svgs_for_pngs = []
  foreach i : range(0, names.length())
    svgs_for_pngs += custom_target(
      'svg-optimized-' + names[i],
      input : raw_svgs[i],
      output : names[i] + '-O.svg',
      command : [
        svgo,
        '-i', '@INPUT@',
        '-o', '@OUTPUT@',
      ],
      build_by_default : true
    )
  endforeach
else
  svgs_for_pngs = raw_svgs
endif

# Making PNG Exports
scales = {
  '0.5': '48',
  '1': '96',
  '1.5': '144',
  '2': '192',
  '2.5': '240',
  '3': '288',
  '3.5': '336',
  '4': '384',
}

foreach i : range(0, names.length())
  foreach scale, dpi : scales
    custom_target(
      'png-' + scale + '-' + names[i],
      input : svgs_for_pngs[i],
      output : names[i] + '@' + scale + '.png',
      env : inkscape_env,
      command : [
        inkscape,
        '@INPUT@',
        '--export-type=png',
        '--export-dpi=' + dpi,
        '--export-filename=@OUTPUT@'
      ],
      build_by_default : true
    )
  endforeach
endforeach
