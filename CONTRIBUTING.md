# Contributing

Issues, discussions, pull requests, and forks may be created at the contributor’s discretion.


## Repository structure

```
.
├── benchmark/              # Result of performance tests
├── doc/                    # Protocol and firmware documentation
│   └── canable2kai.wiki    # Git subtree (external wiki repo)
├── test/                   # Test scripts for system test
│   └── slcan-tester        # Git subtree (external repo)
└── canable2kai-fw/         # Firmware source code
```


## Subtrees (for maintainer)

`doc/` and `test/` are Git subtrees of external repositories.

| Directory | Repository | Sync branch |
|-----------|------------|-------------|
| `doc/`    | [wiki](https://github.com/Nakakiyo092/canable2kai/wiki) (`canable2kai.wiki.git`) | `master` |
| `test/`   | [slcan-tester](https://github.com/Nakakiyo092/slcan-tester) | `merge` |

Both subtrees were added without `--squash` and include the full history of the external repositories.
Do not use `--squash` when pulling.

### Setup

Register the remotes once per clone:

```
git remote add doctree https://github.com/Nakakiyo092/canable2kai.wiki.git
git remote add testtree https://github.com/Nakakiyo092/slcan-tester.git
```

The subtrees were added with the commands below.
They are listed for reference only and do not need to be run again.

```
git subtree add --prefix=test testtree main
git subtree add --prefix=doc doctree master
```

### Sync

It would be a good practice to sync at release time.
Run the commands on a clean working tree (check with `git status`).

Documentation: the wiki is updated directly on `master`.
Pull first so that edits made on the wiki web page are merged before pushing.

```
git subtree pull --prefix=doc doctree master
git subtree push --prefix=doc doctree master
```

Tests: slcan-tester is synced through the working branch `merge`.
Create `merge` from `main` in slcan-tester before syncing, then merge it into `main` with a pull request.

```
git subtree pull --prefix=test testtree merge
git subtree push --prefix=test testtree merge
```


## Backward compatibility

- Compatibility with LAWICEL CAN ASCII protocol is mandatory.
- Compatibility with the SLCAN protocol, including older versions in this repository, is not required.
- Nevertheless, breaking changes should be limited to major releases.


## Test policy

- Review individual test cases as needed before submitting a pull request.
- Confirm all standard test cases before releasing firmware.
- Visually inspect the pre-release checklist prior to release.

## Test coverage

- Every requirement described in the documents under `doc/` should be covered by at least one test.
- Beyond that, branch or edge-case coverage is added at the developer's discretion — wherever there is doubt about correctness, add a test.
