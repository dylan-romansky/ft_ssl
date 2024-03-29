ft_ssl is a recoding of some of the features of openssl.
The project consists of 3 sub-projects, each turned in
individually: hashing, symmetric encryption, and asymmetric
encryption. The project is designed to be perfectly compatible
with the version of openssl available on OSX. As such I've
noticed a few key differences between the openssl available on
my linux laptop and the openssl available on my school's Mac
desktops:

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

At the time of writing this README I also have not yet
implemented the rsa/asymmetric encryption part of the project.


Goals of this project include familiarizing ourselves with bitwise logic and how data is handled at the byte level as well as giving us a rudimentary understanding of algorithms in a security context. Because of the aforementioned, debugging this project is a nightmare as the tiniest difference in behaviour causes a snowball effect, produciing output that gives you no real indication of what the exact mistake is.
