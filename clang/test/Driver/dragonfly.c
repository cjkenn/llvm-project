// RUN: %clang --target=x86_64-pc-dragonfly --sysroot= -### %s 2>&1 | FileCheck %s

// CHECK: "-cc1" "-triple" "x86_64-pc-dragonfly"
// CHECK: ld{{.*}}" "--eh-frame-hdr" "-dynamic-linker" "/usr/libexec/ld-elf.so.{{.*}}" "--hash-style=gnu" "--enable-new-dtags" "-o" "a.out" "{{.*}}crt1.o" "{{.*}}crti.o" "{{.*}}crtbegin.o" "-L{{.*}}/../lib" "-L/usr/lib" "-L/usr/lib/gcc80" "{{.*}}.o" "-rpath" "{{.*}}gcc80{{.*}}" "-lc" "-lgcc" "{{.*}}crtend.o" "{{.*}}crtn.o"

// Check x86_64-unknown-dragonfly, X86_64
// RUN: %clang -### %s 2>&1 --target=x86_64-unknown-dragonfly \
// RUN:     --sysroot=%S/Inputs/basic_dragonfly_tree \
// RUN:   | FileCheck --check-prefix=CHECK-LD-X86_64 %s
// CHECK-LD-X86_64: "-cc1" "-triple" "x86_64-unknown-dragonfly"
// CHECK-LD-X86_64-SAME: "-isysroot" "[[SYSROOT:[^"]+]]"
// CHECK-LD-X86_64: "{{.*}}ld{{(.exe)?}}"
// CHECK-LD-X86_64-SAME: "[[SYSROOT]]{{/|\\\\}}usr{{/|\\\\}}lib{{/|\\\\}}crt1.o"
// CHECK-LD-X86_64-SAME: "[[SYSROOT]]{{/|\\\\}}usr{{/|\\\\}}lib{{/|\\\\}}crti.o"
// CHECK-LD-X86_64-SAME: "[[SYSROOT]]{{/|\\\\}}usr{{/|\\\\}}lib{{/|\\\\}}gcc80{{/|\\\\}}crtbegin.o"
// CHECK-LD-X86_64-SAME: "-L[[SYSROOT]]{{/|\\\\}}usr{{/|\\\\}}lib" "-L[[SYSROOT]]{{/|\\\\}}usr{{/|\\\\}}lib{{/|\\\\}}gcc80"
// CHECK-LD-X86_64-SAME: "-rpath" "/usr/lib/gcc80" "-lc" "-lgcc" "--as-needed" "-lgcc_pic" "--no-as-needed"
// CHECK-LD-X86_64-SAME: "[[SYSROOT]]{{/|\\\\}}usr{{/|\\\\}}lib{{/|\\\\}}gcc80{{/|\\\\}}crtend.o"
// CHECK-LD-X86_64-SAME: "[[SYSROOT]]{{/|\\\\}}usr{{/|\\\\}}lib{{/|\\\\}}crtn.o"

// -r suppresses -dynamic-linker, default -l and crt*.o like -nostdlib.
// RUN: %clang -### %s --target=x86_64-pc-dragonfly -r \
// RUN:   2>&1 | FileCheck %s --check-prefix=RELOCATABLE
// RELOCATABLE:     "-r"
// RELOCATABLE-NOT: "-dynamic-linker"
// RELOCATABLE-NOT: "-l
// RELOCATABLE-NOT: {{.*}}crt{{[^./]+}}.o

// Check that the new linker flags are passed to DragonFly
// RUN: %clang --target=x86_64-unknown-dragonfly -s -t -### %s 2>&1 \
// RUN:   | FileCheck --check-prefix=CHECK-LD-FLAGS %s
// CHECK-LD-FLAGS: ld{{.*}}" "{{.*}}" "-s" "-t"
