
class cstuff {

  Exec {
    path => '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin',
  }

  exec {'runupdate':
    command => 'apt-get update',
    creates => '/usr/bin/updatedonce',
  }

# perhaps package?? check availability
#exec {'valgrind':
 # command => 'apt-get -y install valgrind',
  #require => Exec['runupdate'],
  #}

  package{'valgrind':
    ensure  => installed,
    require => Exec['runupdate'],
  }

}


include cstuff

