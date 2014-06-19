
class cstuff {

  Exec {
    path => '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin',
  }

  exec {'runupdate':
    command => 'apt-get update',
    creates => '/usr/bin/updatedonce',
  }

  package {['valgrind', 'gdb']:
    ensure  => installed,
    require => Exec['runupdate'],
  }

  package {'make':
    ensure => installed,
  }

}

include cstuff
