ft_ssl is a recoding of some of the features of openssl.
The project consists of 3 parts: hashing, symmetric
encryption, and asymmetric encryption. The project is designed
to be perfectly compatible with the version of openssl
available on OSX. As such I've noticed a few key differences
between the openssl available on my linux laptop and the
openssl available on my school's Mac desktops:

-On my laptop all encryptions appear to be salted. This is not
 the case on my school's Macs.

-All encryptions expect a password to be present. On the
 school Macs des-ecb and the variations thereof do not
 require this.
--As a result of this, all encryptions will be prepended with
  "Salted__" whereas this isn't always true on the school Macs

-The pbkdf on the school Macs is just an md5 hash. I haven't
 yet figured out what it is on my laptop.

I have recently overhauled the bulk of the executable in order
to bufferize my input, thus allowing me to hash/encrypt files
of arbitrary length. As a result of this I'm not completely
sure the cipher algorithms work as they're supposed to yet. I
will need to get access to the version of openssl used on my
school's Macs to be able to properly verify. The hashing
algorithms have been tested and verified working on files
several gigabytes in size.
