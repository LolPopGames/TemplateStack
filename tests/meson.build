tests = [
  {
    'name': 'base',
    'cases': [
      ['Initialization', 'init'],
      ['Push-Pop-Peek', 'push-pop-peek'],
      ['Is Empty or Full', 'is-empty-full'],
      ['Size & Buffer Size', 'size'],
      ['Buffer Managment', 'buffer'],
      ['Memory Allocation', 'alloc']
    ]
  },
  {
    'name': 'fail',
    'cases': [
      ['Inserting NULL instead of &stack', 'null'],
      ['Inserting stack with NULL buffer', 'buffer-null']
    ]
  },
  {
    'name': 'types',
    'cases': [
      ['Names', 'names'],
      ['Various Values', 'values']
    ]
  }
]

foreach suite : tests
  foreach t : suite['cases']
    test(
      t[0] + ' test',

      executable(
        suite['name'] + '_' + t[1],
        suite['name'] + '/' + t[1] + '.c',
        c_args : ['-I..', '-Wno-all', '-std=c89', '-pedantic']
      ),

      suite : suite['name']
    )
  endforeach
endforeach
