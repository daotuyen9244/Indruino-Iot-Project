#!/bin/bash -eux

ROOT_DIR=$(dirname $0)/../../
<<<<<<< HEAD
FUZZING_DIR=${ROOT_DIR}/extras/fuzzing/

export CC="clang-${CLANG}"
export CXX="clang++-${CLANG}"
cmake -DCMAKE_BUILD_TYPE=Debug .

FUZZER_TARGET="${FUZZER}_fuzzer"
FUZZER_PATH="extras/fuzzing/${FUZZER_TARGET}"
CORPUS_DIR="${FUZZING_DIR}/${FUZZER}_corpus"
SEED_CORPUS_DIR="${FUZZING_DIR}/${FUZZER}_seed_corpus"

cmake --build . --target $FUZZER_TARGET

export ASAN_OPTIONS="detect_leaks=0"
export LLVM_PROFILE_FILE="${FUZZER_TARGET}.profraw"
${FUZZER_PATH} "$CORPUS_DIR" "$SEED_CORPUS_DIR" -max_total_time=60 -timeout=1

llvm-profdata-${CLANG} merge -sparse ${LLVM_PROFILE_FILE} -o ${FUZZER_TARGET}.profdata
llvm-cov-${CLANG} report ./${FUZZER_PATH} -instr-profile=${FUZZER_TARGET}.profdata
=======
INCLUDE_DIR=${ROOT_DIR}/src/
FUZZING_DIR=${ROOT_DIR}/extras/fuzzing/
CXXFLAGS="-g -fprofile-instr-generate -fcoverage-mapping -fsanitize=address,undefined,fuzzer -fno-sanitize-recover=all"

fuzz() {
	NAME="$1"
	FUZZER="${NAME}_fuzzer"
	FUZZER_CPP="${FUZZING_DIR}/${NAME}_fuzzer.cpp"
	CORPUS_DIR="${FUZZING_DIR}/${NAME}_corpus"
	SEED_CORPUS_DIR="${FUZZING_DIR}/${NAME}_seed_corpus"

	clang++-${CLANG} ${CXXFLAGS} -o ${FUZZER} -I$INCLUDE_DIR ${FUZZER_CPP}

	export ASAN_OPTIONS="detect_leaks=0"
	export LLVM_PROFILE_FILE="${FUZZER}.profraw"
	./${FUZZER} "$CORPUS_DIR" "$SEED_CORPUS_DIR" -max_total_time=30 -timeout=1

	llvm-profdata-${CLANG} merge -sparse ${LLVM_PROFILE_FILE} -o ${FUZZER}.profdata
	llvm-cov-${CLANG} report ./${FUZZER} -instr-profile=${FUZZER}.profdata
}

fuzz json
fuzz msgpack
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
