# Introduction

# Prerequisites

Install [Dart](https://dart.dev/get-dart)

```
dart pub get
```
### For Debian-based

```
apt -y install gcc cmake
```

### For Fedora-based
```
yum -y install gcc cmake
```

### For Arch-based
```
yay -S gcc cmake
```

# Running

```
cmake .
make
cd dart && dart pub get && dart run lib/main.dart
```