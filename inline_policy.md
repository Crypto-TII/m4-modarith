## Inline policy

We have four main choices regarding inlining policy:
- **InlinePolicy.SIZE**: Never inline any functions. Sacrifices speed for size.
- **InlinePolicy.BALANCED_SIZE**: Inline some functions. Sacrifices some size for speed.
- **InlinePolicy.BALANCED_SPEED**: Inline more functions, always inlining small ones. Sacrifices some speed for size.
- **InlinePolicy.SPEED**: Always inline every function. Sacrifices size for speed.

We recommend using `BALANCED_SPEED`, which is the default. To choose a different policyu, one must set the parameter `inline_policy` to one of the enumerations above during class construction. For example, for choosing `BALANCED_SIZE`, you could change the following in the `m4generator.py`, from this standard initialization:

```
g = CodeGenerator(p)
```

towards this one:

```
g = CodeGenerator(p, inline_policy=InlinePolicy.BALANCED_SIZE)
```

Additionally, there is a CMake option for the project called `UNROLL_LOOPS`, which further trades off size for speed if turned on.