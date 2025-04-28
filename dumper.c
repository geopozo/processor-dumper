#include <stdio.h>

#define YELLOW "\x1b[33m"
#define RESET  "\x1b[0m"

struct Feature {
    int bit;
    const char *name;
    const char *desc;
    const char *usecase;
};

/* CPUID(1).EDX features */
struct Feature cpuid1_edx[] = {
    {0,  "FPU",    "Floating Point Unit",                "Required for all floating-point math operations."},
    {1,  "VME",    "Virtual 8086 Mode Enhancements",     "Legacy 16-bit mode virtualization support."},
    {2,  "DE",     "Debug Extensions",                   "Enhanced debugging capabilities for trap handling."},
    {3,  "PSE",    "Page Size Extension",                "4MB pages support to reduce TLB pressure."},
    {4,  "TSC",    "Timestamp Counter",                  "High-res cycle counter for profiling and timing."},
    {5,  "MSR",    "Model Specific Registers",           "Access to performance and control registers."},
    {6,  "PAE",    "Physical Address Extension",         ">4GB RAM addressing on 32-bit systems."},
    {7,  "MCE",    "Machine Check Exception",            "Hardware error detection and reporting."},
    {8,  "CX8",    "CMPXCHG8 Instruction",               "Atomic compare-and-swap on 64-bit values."},
    {9,  "APIC",   "Advanced Programmable Interrupt Controller", "SMP interrupt routing and management."},
    {11, "SEP",    "SYSENTER/SYSEXIT",                   "Fast system calls for low-overhead transitions."},
    {12, "MTRR",   "Memory Type Range Registers",        "Cache policy control per memory region."},
    {13, "PGE",    "Page Global Enable",                 "Global TLB entries persist across context switches."},
    {14, "MCA",    "Machine Check Architecture",         "Advanced machine-check error reporting."},
    {15, "CMOV",   "Conditional Move",                   "Branch-free data-dependent moves for pipelining."},
    {16, "PAT",    "Page Attribute Table",               "Extended cache attribute control."},
    {17, "PSE-36", "36-bit Page Size Extension",         "Large pages on >4GB RAM for legacy systems."},
    {19, "CLFLUSH","CLFLUSH Instruction",               "Explicit cache line flush—used in device drivers."},
    {23, "MMX",    "MMX Instructions",                   "Legacy 64-bit SIMD for multimedia workloads."},
    {24, "FXSR",   "FXSAVE/FXRSTOR Instructions",       "Fast FPU/SIMD context save/restore."},
    {25, "SSE",    "Streaming SIMD Extensions",          "128-bit float SIMD for graphics and audio."},
    {26, "SSE2",   "Streaming SIMD Extensions 2",        "Double-precision SIMD and integer SIMD ops."},
    {28, "HTT",    "Hyper-Threading Technology",         "Logical cores per physical core for parallelism."},
};

/* CPUID(1).ECX features */
struct Feature cpuid1_ecx[] = {
    {0,  "SSE3",       "Streaming SIMD Extensions 3",   "Horizontal add/sub and complex arithmetic enhancements."},
    {1,  "PCLMULQDQ",  "Carry-less Multiplication",      "Crypto acceleration (GCM/AES-GCM)."},
    {9,  "SSSE3",      "Supplemental SSE3",             "Sub-byte shuffles and improved vector math."},
    {12, "FMA",        "Fused Multiply-Add",           "Single-instruction multiply-and-add for ML/DSP."},
    {19, "SSE4.1",     "Streaming SIMD Extensions 4.1", "Dot-product and blend ops for media processing."},
    {20, "SSE4.2",     "Streaming SIMD Extensions 4.2", "String and CRC32 acceleration."},
    {23, "POPCNT",     "Population Count",              "Fast bit-counting used in compression and crypto."},
    {25, "AES",        "AES Instructions",              "Hardware AES encryption for secure communications."},
    {28, "AVX",        "Advanced Vector Extensions",   "256-bit float SIMD for heavy numeric/ML workloads."},
};

/* CPUID(7,0).EBX features */
struct Feature cpuid7_ebx[] = {
    {0,  "FSGSBASE",          "RDFSBASE/WRFSBASE Instructions", "User-mode FS/GS base access for faster TLS and context switching."},
    {1,  "TSC_ADJUST",        "TSC Adjustment MSR",             "Adjust timestamp counter for hypervisor sync."},
    {2,  "SGX",               "Software Guard Extensions",      "Hardware enclaves for secure computation."},
    {3,  "BMI1",              "Bit Manipulation Instructions 1", "ANDN/BEXTR/T1MSK for fast bitfield operations."},
    {4,  "HLE",               "Hardware Lock Elision",          "Transactional memory hint for optimistic concurrency."},
    {5,  "AVX2",              "Advanced Vector Extensions 2",   "256-bit integer SIMD—graphics, ML, crypto."},
    {7,  "SMEP",              "Supervisor Mode Execution Protection", "Prevents kernel from executing user-mode code."},
    {8,  "BMI2",              "Bit Manipulation Instructions 2", "PEXT/PDEP for parallel bitfield extract/deposit."},
    {9,  "ERMS",              "Enhanced REP MOVSB/STOSB",       "Optimized block memory copy/set instructions."},
    {10, "INVPCID",           "Invalidate Process-Context ID",  "Fine-grained TLB invalidation for virtualization."},
    {11, "RTM",               "Restricted Transactional Memory","User-level Intel TSX transactional support."},
    {18, "RDSEED",            "Hardware Random Seed",           "Secure seed generation for RNG initialization."},
    {19, "ADX",               "Multi-Precision Add-Carry",      "ADDX/ADCX for fast big-integer arithmetic."},
    {29, "SHA",               "SHA Instruction Extensions",     "Hardware SHA-1/SHA-256 hashing acceleration."},
};

/* CPUID(7,0).ECX features (AVX-512 subsets) */
struct Feature cpuid7_ecx[] = {
    {0,  "AVX512F",       "AVX-512 Foundation",           "512-bit SIMD for HPC and ML."},
    {1,  "AVX512DQ",      "AVX-512 Double/Quad",          "Extended vector integer ops for data crunching."},
    {3,  "AVX512IFMA",    "Integer FMA",                  "Multiprecision math and deep learning integer kernels."},
    {4,  "AVX512PF",      "Prefetch",                     "Prefetch hints for large-data streaming workloads."},
    {5,  "AVX512ER",      "Exponential & Reciprocal",     "Specialized math functions for scientific computation."},
    {6,  "AVX512CD",      "Conflict Detection",           "Cache conflict hints for gather/scatter operations."},
    {8,  "AVX512BW",      "Byte & Word",                  "8/16-bit data operations in 512-bit registers."},
    {9,  "AVX512VL",      "Vector Length Extensions",     "128/256-bit variants of AVX-512 instructions."},
};

/* CPUID(7,0).EDX features */
struct Feature cpuid7_edx[] = {
    {1,  "AVX512VBMI",    "Vector Bit Manipulation",      "Byte/word permute and mask operations in 512-bit registers."},
    {3,  "UMIP",          "User Mode Instruction Prevention", "Prevents certain privileged instructions in user mode."},
    {8,  "PKU",           "Protection Keys for Userspace", "Memory protection domains in user-space without syscalls."},
    {10, "OSPKE",         "OS-Based PKU Enable",          "OS permission for user-space PKU usage."},
    {26, "CLWB",          "Cache Line Write Back",        "Writes back cache lines to memory without invalidation."},
    {27, "CLFLUSHOPT",    "Optimized Cache Flush",        "Non-blocking cache flush for high-performance persistence."},
    {29, "PTWRITE",       "Patched Write",                "Writes memory/page-table patches for virtualization."},
};

/* CPUID(0x80000001).ECX features (AMD) */
struct Feature cpuid80000001_ecx[] = {
    {5,  "LZCNT",     "Leading Zero Count",           "Counts leading zeros for bit scanning in compression/crypto."},
    {6,  "SSE4a",     "SSE4a Instructions (AMD)",     "AMD-specific SIMD instructions with unique shuffle ops."},
    {8,  "PREFETCHW", "Prefetch Write Hint",         "Prefetch data into cache for write-heavy workloads."},
    {21, "TBM",       "Trailing Bit Manipulation",    "Advanced bitfield ops for crypto and data structures."},
};

/* CPUID(0x80000001).EDX features (AMD) */
struct Feature cpuid80000001_edx[] = {
    {29, "LM",       "Long Mode (64-bit)",            "Enables 64-bit mode—required for modern OS and apps."},
    {31, "3DNOWEX",  "3DNow! Extensions",             "Legacy AMD SIMD—mostly obsolete but present on older CPUs."},
};

void cpuid(unsigned int leaf, unsigned int subleaf,
           unsigned int *eax, unsigned int *ebx,
           unsigned int *ecx, unsigned int *edx) {
    __asm__ volatile("cpuid"
                     : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                     : "a"(leaf), "c"(subleaf));
}

void print_features(unsigned int reg, struct Feature *features, int n) {
    for (int i = 0; i < n; i++) {
        int set = (reg & (1u << features[i].bit)) != 0;
        const char *color = set ? RESET : YELLOW;
        printf("%s[%2d] %-12s : %-30s - %s%s\n",
               color,
               features[i].bit,
               features[i].name,
               features[i].desc,
               features[i].usecase,
               RESET);
    }
}

int main() {
    unsigned int eax, ebx, ecx, edx;
    unsigned int max_basic, max_ext;

    /* Determine supported leaf ranges */
    cpuid(0, 0, &max_basic, &ebx, &ecx, &edx);
    cpuid(0x80000000, 0, &max_ext, &ebx, &ecx, &edx);

    printf("== CPUID(1) Basic Features ==\n");
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    print_features(edx, cpuid1_edx, sizeof(cpuid1_edx)/sizeof(*cpuid1_edx));
    print_features(ecx, cpuid1_ecx, sizeof(cpuid1_ecx)/sizeof(*cpuid1_ecx));

    printf("\n== CPUID(7,0) Extended Features ==\n");
    if (max_basic >= 7) {
        cpuid(7, 0, &eax, &ebx, &ecx, &edx);
        print_features(ebx, cpuid7_ebx, sizeof(cpuid7_ebx)/sizeof(*cpuid7_ebx));
        print_features(ecx, cpuid7_ecx, sizeof(cpuid7_ecx)/sizeof(*cpuid7_ecx));
        print_features(edx, cpuid7_edx, sizeof(cpuid7_edx)/sizeof(*cpuid7_edx));

        /* New: CPUID(7,1) subleaf */
        printf("\n== CPUID(7,1) Sub-leaf 1 Raw Values ==\n");
        cpuid(7, 1, &eax, &ebx, &ecx, &edx);
        printf("EBX: 0x%08X, ECX: 0x%08X, EDX: 0x%08X\n", ebx, ecx, edx);
    } else {
        printf(YELLOW "CPUID(7,0) not supported (max leaf = %u)" RESET "\n", max_basic);
    }

    printf("\n== CPUID(0x80000001) AMD Extended ==\n");
    if (max_ext >= 0x80000001) {
        cpuid(0x80000001, 0, &eax, &ebx, &ecx, &edx);
        print_features(ecx, cpuid80000001_ecx, sizeof(cpuid80000001_ecx)/sizeof(*cpuid80000001_ecx));
        print_features(edx, cpuid80000001_edx, sizeof(cpuid80000001_edx)/sizeof(*cpuid80000001_edx));
    } else {
        printf(YELLOW "CPUID(0x80000001) not supported (max ext = 0x%X)" RESET "\n", max_ext);
    }

    printf("\n== CPUID(0x80000008) Address Size Info ==\n");
    if (max_ext >= 0x80000008) {
        cpuid(0x80000008, 0, &eax, &ebx, &ecx, &edx);
        unsigned int phys_bits = eax & 0xFF;
        unsigned int lin_bits  = (eax >> 8) & 0xFF;
        printf("Physical Address Bits: %u\n", phys_bits);
        printf("Linear Address Bits : %u\n", lin_bits);
    } else {
        printf(YELLOW "CPUID(0x80000008) not supported (max ext = 0x%X)" RESET "\n", max_ext);
    }

    /* Additional leaves */
    printf("\n== CPUID(0xD,0) XSAVE Info ==\n");
    if (max_basic >= 0xD) {
        cpuid(0xD, 0, &eax, &ebx, &ecx, &edx);
        printf("XCR0 supported bits: 0x%08X\n", eax);
    } else {
        printf(YELLOW "CPUID(0xD,0) not supported (max leaf = %u)" RESET "\n", max_basic);
    }

    printf("\n== CPUID(0x14,0) Processor Trace Info ==\n");
    if (max_basic >= 0x14) {
        cpuid(0x14, 0, &eax, &ebx, &ecx, &edx);
        printf("PT capabilities (EAX): 0x%08X\n", eax);
    } else {
        printf(YELLOW "CPUID(0x14,0) not supported (max leaf = %u)" RESET "\n", max_basic);
    }

    return 0;
}


