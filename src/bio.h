/*
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BIO_H
#define __BIO_H

typedef void lazy_free_fn(void *args[]);
typedef void comp_fn(uint64_t user_data);

typedef enum bio_worker_t {
    BIO_WORKER_CLOSE_FILE = 0,
    BIO_WORKER_AOF_FSYNC,
    BIO_WORKER_LAZY_FREE,
    BIO_WORKER_NUM
} bio_worker_t;

/* Background job opcodes */
typedef enum bio_job_type_t {
    BIO_CLOSE_FILE = 0,     /* Deferred close(2) syscall. */
    BIO_AOF_FSYNC,          /* Deferred AOF fsync. */
    BIO_LAZY_FREE,          /* Deferred objects freeing. */
    BIO_CLOSE_AOF,
    BIO_COMP_RQ_CLOSE_FILE,  /* Job completion request, registered on close-file worker's queue */
    BIO_COMP_RQ_AOF_FSYNC,  /* Job completion request, registered on aof-fsync worker's queue */
    BIO_COMP_RQ_LAZY_FREE,  /* Job completion request, registered on lazy-free worker's queue */
    BIO_NUM_OPS
} bio_job_type_t;

/* Exported API */
void bioInit(void);
unsigned long bioPendingJobsOfType(int type);
void bioDrainWorker(int job_type);
void bioKillThreads(void);
void bioCreateCloseJob(int fd, int need_fsync, int need_reclaim_cache);
void bioCreateCloseAofJob(int fd, long long offset, int need_reclaim_cache);
void bioCreateFsyncJob(int fd, long long offset, int need_reclaim_cache);
void bioCreateLazyFreeJob(lazy_free_fn free_fn, int arg_count, ...);
void bioCreateCompRq(bio_worker_t assigned_worker, comp_fn *func, uint64_t user_data);

#endif
