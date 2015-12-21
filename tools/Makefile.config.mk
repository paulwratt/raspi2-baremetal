include .config


auto.conf: .config
 @ ($(foreach v, $(filter CONFIG_%, $(.VARIABLES)), \
 $(if $($v), echo $v='$($v)';))) > $@


autoconf.h: .config
 @ ($(foreach v, $(filter CONFIG_%, $(.VARIABLES)), \
 $(if $($v), echo \#define $v $(if $(filter y,$($v)),1,'$($v)');))) > $@
