---
layout: default
title: "Writing Documentation"
tag: "writingDocumentation"
---

### The library's documentation relies on a [modified version of just-the-docs](https://github.com/rshs-robotics-club/just-the-docs) as its jekyll theme.
The modification allows the documentation  to have infinite nesting on the navigation bar, and a more centralised navigation structure management.

### The centralised file structure management
The structure is stored in a file `docsStructure.yml`.
It should look something like
```yml
FileSystem:
  - Ev3Wrap:
    no_page: true
    display_text: "AAA_BRANCH_NAME_AAA"
    child_folder_reqs:
      - "ev3wrap"
      - "AAA_BRANCH_NAME_AAA"
    children:
    - quickstart:
      tag: "quickstart"
      children:
      - index:
        tag: "introduction"
      - troubleshooting:
        tag: "troubleshooting"

    - documentation:
      tag: "documentation"
      child_folder_reqs:
        - "documentation"
      children:
      - Blockable:
        tag: "Blockable"
      - Button:
        tag: "Button"
      - ColorSensor:
        tag: "ColorSensor"
    - contributing:
      tag: "contribute"
      child_folder_reqs:
        - "contributing"
      children:
      - libraryStructre:
        tag: "libraryStructure"
        child_folder_reqs:
          - "libraryStructure"
        children:
        - CMakeSpecifics:
          tag: "CMakeSpecifics"
        - CMakeExamples:
          tag: "CMakeExamples"
      - writingDocumentation:
        tag: "writingDocumentation"
```
(some files are removed to shorten this wall of text)

each `- <namehere>` represents 1 md file (or page).
for example,
```yml  
- Blockable:
    tag: "Blockable"
``` 
represents the file with the tag "Blockable". This tag is stored in the [front matter](https://jekyllrb.com/docs/front-matter/) of the md file, something like
```
---
layout: default
title: "Blockable"
tag: "Blockable"
---
```
This front matter is processed by [jekyll](https://jekyllrb.com/) using instructions stored in our [modified just-the-docs theme](https://github.com/rshs-robotics-club/just-the-docs).
The instructions in the theme tells jekyll to read through `docStructure.yml` to decide how to construct the navigation bar.

---

# page urls
are decided based on the folder structure
(e.g. `/docs/documentation/Blockable.md` will show up in `https://rshs-robotics-club.github.io/ev3wrap/unstable/documentation/BlockableDocumentation.html`)

---
There is a lot more detail we haven't gone through in this guide, which will be added later.
