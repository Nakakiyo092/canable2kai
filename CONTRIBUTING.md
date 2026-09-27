# Contributing

Issues, discussions, and forks may be created at the contributor’s discretion.
Pull requests are not expected to be accepted.


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


## Subbtreess (For maintainer)

```
git remote add doctree https://github.com/Nakakiyo092/canable2kai.wiki.git
git remote add testtree https://github.com/Nakakiyo092/slcan-tester
```

```
git status
git subtree add --prefix=test testtree main
git subtree add --prefix=doc doctree master
```

The commands below sync changes between this repository and the subtrees
([wiki](https://github.com/Nakakiyo092/canable2kai/wiki) and [slcan-tester](https://github.com/Nakakiyo092/slcan-tester)).
It would be a good practice to sync at release time.

```
git subtree pull --prefix=doc doctree master
git subtree push --prefix=doc doctree master
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
