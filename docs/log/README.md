# GP-Log2 & Logarithmic Exposure

**Understanding GoPro's Log Base 600 Encoding, Exposure Strategy, and LUT-Based Color Grading**

---

## Table of Contents

1. Introduction
2. What Is a Logarithmic Encoding?
3. GP-Log2: Log Base 600 Explained
4. Color Primaries: Rec.2020 and Why It Matters
5. Exposing with GP-Log2 in the Field
6. Understanding the EV Compensation Parameter
7. Highlight Protection vs. Shadow Protection
8. The Highlight Rolloff Option
9. Color Space Output: Rec.709 vs. Rec.2020
10. How the [LUT Generator](https://gopro.github.io/labs/gplog2/) Works

---

## 1. Introduction

Modern cameras capable of capturing logarithmic video offer a significant advantage over standard gamma footage: far greater dynamic range is encoded into the same 10-bit signal. GoPro Mission 1 series cameras using the **GP-Log2** profile are no exception. Rather than mapping scene luminance to a display-ready gamma curve — discarding data in the process — GP-Log2 compresses an extremely wide tonal range into a manageable digital signal that retains information in both shadows and highlights for later processing.

However, this flexibility introduces complexity. Log footage looks flat and desaturated straight out of the camera, and requires a **Look-Up Table (LUT)** to restore it to a pleasing, display-ready image. More importantly, the exposure decisions made at the time of capture directly determine how much of the scene's dynamic range ends up in each zone of the log signal — and therefore how much latitude you have in post.

This white paper explains how GP-Log2 works mathematically, how to use it intelligently in the field, and how the GP-Log2 LUT Generator tool translates your exposure intent into a precise color transform.

---

## 2. What Is a Logarithmic Encoding?

A **linear** encoding maps scene light directly to a code value: doubling the light doubles the number. This mirrors physical reality but wastes bit depth — human vision is not linear. We are far more sensitive to changes in dark tones than bright ones.

A **logarithmic** encoding compresses the signal using a log function, allocating more code values to dark regions (where the eye is most sensitive). The result is a signal that behaves more like human perception and packs far more dynamic range into the same number of bits.

The tradeoff is that log footage looks 'wrong' on a standard display. A dedicated transform — a LUT — must undo the log encoding and map the signal to the appropriate output color space and transfer function before viewing.

### Linear vs. Log: A Concrete Example

Suppose a scene contains 12 stops of dynamic range. With a linear encoding in 10 bits (1024 values), the top stop (the brightest octave) uses 512 values, the next stop uses 256, and so on. The bottom stop (10th, not 12th) gets just one code value — 10-bit linear can only encode 10-stop maximum.

With a log encoding, each stop receives roughly the same number of code values regardless of brightness. All 12 stops are encoded with comparable precision, preserving shadow details.

---

## 3. GP-Log2: Log Base 600 Explained

GP-Log2 uses a **logarithm of base 600** to encode scene luminance. The base number is the key design parameter: it determines how much dynamic range is packed into the 0–1 signal range and how the tones are distributed across that range.

### The Forward Transform (Capture)

Given a linear scene value *L* (where 0 = black, 1 = clipped white), GP-Log2 encodes it as:

```
GP-Log2(L) = log₆₀₀(L × (600 − 1) + 1)
           = log(L × 599 + 1) / log(600)
```

This maps:
- L = 0.0000 (pure black) → 0.000
- L = 0.0517 (18% grey) → ~0.542
- L = 0.2500 (2 stops from clipping) → ~0.784
- L = 0.5000 (1 stop from clipping) → ~0.892
- L = 1.0000 (clipped white) → 1.000

### The Inverse Transform (Decoding in a LUT)

To recover linear light from a GP-Log2 code value *v* (normalized 0 to 1):

```
L = (600ᵛ − 1) / (600 − 1)
```

This is the first operation performed by the LUT generator when building a .cube file.

### Why Base 600?

The base controls the **compression ratio** of the curve:

- A **higher base** compresses the highlights more aggressively and encodes greater dynamic range, but allocates fewer code values to each stop — reducing per-stop precision.
- A **lower base** is gentler, preserving more precision per stop but encoding a narrower dynamic range.

Base 600 represents GoPro's engineering decision for the dynamic range capability of their sensors and the bit depth of their recording formats. It is a relatively high log-base, designed to encode up to 14 stops of dynamic range into an 10-bit signal.

---

## 4. Color Primaries: Rec.2020 and Why It Matters

GP-Log2 footage is encoded with **Rec.2020 color primaries** — the same wide color gamut used in HDR broadcast and cinema production. Rec.2020 encompasses a significantly larger portion of the CIE color space than the Rec.709 primaries used by standard HD displays.

### Practical Implications

When GP-Log2 is decoded, the resulting linear RGB values live in Rec.2020 space. If displayed directly on a Rec.709 monitor (the standard for most HD screens), colors will appear desaturated.

The LUT must therefore include a **color matrix transform** that converts from Rec.2020 primaries to the target display space. Without this step, even a correctly exposed, correctly decoded image will have inaccurate colors.

### The Rec.2020 → Rec.709 Matrix

The transform used in the LUT generator is the standard industry matrix:

```
R₇₀₉ =  1.6605·R₂₀₂₀ − 0.5876·G₂₀₂₀ − 0.0728·B₂₀₂₀
G₇₀₉ = −0.1246·R₂₀₂₀ + 1.1329·G₂₀₂₀ − 0.0083·B₂₀₂₀
B₇₀₉ = −0.0182·R₂₀₂₀ − 0.1006·G₂₀₂₀ + 1.1187·B₂₀₂₀
```

Note that this matrix produces **negative values** for out-of-gamut colors — colors that exist in Rec.2020 but not in Rec.709. This is expected and correct. These negative values should be preserved in the .cube file for NLEs that support extended-range LUTs; clamping them to zero loses colorimetric accuracy.

---

## 5. Exposing with GP-Log2 in the Field

Because GP-Log2 compresses tones non-linearly, the exposure strategy you use at capture time has an effect on the quality of the final grade. Unlike JPEG or standard gamma video, where exposure mistakes are largely permanent, GP-Log2 gives you significant latitude — but only if you make deliberate choices about where you place your exposure.

The GoPro camera exposes for the world (in Auto) using the linear light data. Exposure for color mode like GP-Log2, Flat, Cinematic, Natural or Vibrant, and are all starting with similar shutter and ISO settings. GP-Log2 will just appear brighter, on the LCD or timeline. The GoPro exposure logic is protecting about 1.8+ stops of highlights above reflected white. 
This is why the LUT Generation tool defaults to adding 1.8EV to Rec709 output.  If you create a monitoring LUT for a Rec709 display, +1.8EV within the LUT will match the GoPro's exposure.  
If you set the camera to -1EV, or manual setting to similar effect, to protect an additional stop of highlights, you could compensate will an additional stop into the preview LUT (set +2.8EV.)  You can then exposure for 18% grey through your monitor LUT, knowing the amount of highlight protected.

### Three Exposure Strategies

#### Strategy 1: Expose for Middle Grey (Balanced)

Place 18% grey at the GP-Log2 midpoint, approximately code value 554 out of 1023 (roughly 54%). This gives the maximum balanced latitude.

**Best for:** Scenes with balanced dynamic range, controlled lighting, and predictable content.

**EV Compensation in the LUT:** Moderate positive offset (typically +1.8 EV) to restore the camera's intentional underexposure relative to display gamma.

#### Strategy 2: Expose to Protect Highlights (ETTR — Expose To The Right)

Allow the mid-tones to fall slightly lower than nominal, keeping highlights from clipping. Since the GP-Log2 curve is flat in the highlights, even severely bright areas can be recovered if they remain below the digital clip point.

**Best for:** High-contrast outdoor scenes, sunlit environments, any scenario where blown highlights are unacceptable (e.g., sky, windows, specular reflections).

**EV Compensation in the LUT:** A higher positive offset (e.g., +2.0 to +2.5 EV) to restore underexposed mid-tones. The highlights, which were preserved in the log signal, will now be correctly rendered.

#### Strategy 3: Expose to Protect Shadows

Allow the mid-tones and highlights to sit higher, ensuring shadows are lifted above the noise floor. This sacrifices highlight headroom in exchange for cleaner, less noisy shadow detail.

**Best for:** Night scenes, dimly lit interiors, situations where shadow noise is the primary concern.

**EV Compensation in the LUT:** A lower positive offset (e.g., +1.0 to +1.5 EV) since the camera exposed brighter than nominal.

---

## 6. Understanding the EV Compensation Parameter

The **EV Compensation** slider in the LUT generator is the primary exposure correction control. It applies a linear gain to the decoded signal before the output transfer function is applied.

### The Math

An EV compensation value of *n* applies a gain of 2ⁿ to the linear RGB values:

```
L_output = L_linear × 2ⁿ
```

| EV Value | Linear Gain | Practical Effect |
|----------|------------|-----------------|
| 0.0 EV | ×1.00 | No correction |
| +1.0 EV | ×2.00 | One stop brighter |
| +1.8 EV | ×3.48 | Default — matches camera metering |
| +2.0 EV | ×4.00 | Two stops brighter |
| +3.0 EV | ×8.00 | Three stops brighter |

### Why +1.8 EV is the Default

GoPro cameras exposing with GP-Log2 intentionally underexpose the sensor to protect highlights, placing 18% grey at a lower code value than a standard gamma camera would. The +1.8 EV default in the LUT generator is calibrated to restore 18% grey to its correct display value when using nominal camera metering. This is not arbitrary — it reflects the camera manufacturer's intended middle-grey placement for this log format.

If your footage was shot with deliberate exposure compensation (e.g., +1 stop for shadow protection), you would reduce the LUT's EV compensation by the same amount to maintain correct output.

### EV Compensation vs. Exposure in Post

It is important to understand that adjusting the EV slider in the LUT generator does **not** recover data that was not captured. If highlights clipped at the sensor level, no amount of LUT adjustment will restore them. The EV compensation only determines how the captured log signal maps to the output display range.

---

## 7. Highlight Protection vs. Shadow Protection

The relationship between capture exposure and LUT EV compensation can be understood as a sliding tradeoff along the dynamic range.

### The Dynamic Range Budget

Assume the camera captures up to 14 stops of dynamic range. The log signal encodes all 14 stops with roughly equal code value spacing. When the LUT is applied with a given EV compensation, it determines where "display white" and "display black" fall within those 14 stops:

```
Display white = (camera middle grey) + (stops above grey in scene) − (EV compensation)
Display black = (camera middle grey) − (stops below grey in scene) + (EV compensation)
```

A higher EV compensation shifts the entire tone map upward — recovering shadow detail at the expense of highlight headroom. A lower EV compensation preserves more highlight information at the expense of shadow brightness.

### Practical Pairing: Capture and LUT Together

| Capture Strategy | Exposure Offset | LUT EV Setting | Result |
|-----------------|----------------|----------------|--------|
| Normal / Middle Grey | ±0 | +1.8 EV | Balanced grade, full dynamic range |
| Protect Highlights | −1 stop (dark) | +2.8 EV | Highlights preserved, shadows may be darker |
| Protect Shadows | +1 stop (bright) | +0.8 EV | Shadows bright and clean, highlights at risk |
| Maximum Highlight Headroom | −2 stops | +3.8 EV* | Maximum highlight recovery, noisy shadows |

*Values above +3.0 EV push beyond the LUT generator's slider range; apply additional gain in the NLE.

---

## 8. The Highlight Rolloff Option

The **Highlight Rolloff** feature applies a multi-stage HSV-space (Hue Saturation Value) compression to the decoded image before the output transfer function. It is designed to produce a more film-like response to overexposure rather than a hard digital clip.

### When to Use Rolloff

The rolloff is most useful when:

- Shooting high-contrast scenes where some clipping is unavoidable
- Working with footage that was exposed slightly hot (overexposed)
- Wanting a more analog/film-like response in the highlights rather than a hard clip
- Grading for emotional or stylistic reasons where retained highlight color matters

The rolloff is less appropriate when:

- Delivering for broadcast with strict legal level requirements
- The footage was well-exposed and no highlight protection is needed
- Maximum colorimetric accuracy is required (the compression alters color relationships)
- When you want control over you clipping point in post

### Rolloff and the Clamp Output Setting

When using Rolloff without output clamping, values may still extend slightly above 1.0 in some color channels. If your NLE supports extended-range LUTs, leave clamping off — the NLE will handle out-of-range values correctly. For NLEs that require legal-range .cube files, enable "Clamp Output 0–1" to ensure compatibility.

---

## 9. Color Space Output: Rec.709 vs. Rec.2020

The output color space selection determines the target primaries for the graded image.

### Rec.709

The standard color space for HD broadcast, web streaming, and most consumer display. Rec.709 has a relatively small gamut — it covers approximately 35% of visible colors. Most computer monitors, televisions, and mobile devices display Rec.709 accurately.

**Choose Rec.709 when:**
- Delivering for standard HD broadcast or streaming
- Monitoring on a standard HD display
- The final destination is YouTube in Rec.709, Vimeo, or similar platforms
- Working in a standard SDR workflow

### Rec.2020

A wide-gamut color space covering approximately 76% of visible colors, originally developed for ultra-high-definition broadcast and HDR production. Rec.2020 is significantly larger than Rec.709 and encompasses virtually all of cinema's DCI-P3 gamut.

When Rec.2020 is selected as the output, the LUT generator skips the Rec.2020 → Rec.709 matrix transform, leaving the decoded signal in its native wide-gamut space and applying only the EV compensation, rolloff, and output transfer function.

**Choose Rec.2020 when:**
- Delivering for UHD HDR broadcast (HDR10, HLG)
- Working with a wide-gamut or HDR-capable NLE pipeline
- The downstream color management system will handle the Rec.2020 → display gamut mapping
- Using the LUT as an intermediate step in a larger color pipeline

---

## 10. How the LUT Generator Works

The GP-Log2 [LUT Generator](https://gopro.github.io/labs/gplog2/) produces a 3D LUT in the industry-standard .cube format. Understanding how it builds the LUT clarifies why each setting matters.

### 3D LUT Structure

A 3D LUT is a three-dimensional lookup table indexed by R, G, and B input values. For a LUT of size N, the generator creates N³ entries — one for each combination of N evenly-spaced input values in each channel.

For a 33-point LUT (33³ = 35,937 entries), each input value is spaced 1/32nd of the way across the 0–1 range. Values between entries are interpolated by the NLE.

### The Transform Pipeline

For each of the N³ input triplets (r, g, b):

1. **GP-Log2 Decode:** Apply the inverse log transform to convert from log code values to linear light in Rec.2020 space.

2. **Color Matrix:** If Rec.709 output is selected, multiply by the 3×3 Rec.2020 → Rec.709 matrix. If Rec.2020 output is selected, skip this step.

3. **EV Gain:** Multiply all channels by 2^EV to apply the exposure compensation.

4. **Highlight Rolloff:** If enabled, apply the multi-stage HSV compression sequence.

5. **Output Transfer Function:** Apply the Rec.709 OETF (gamma encode) to convert from linear light to display-ready signal. The OETF is extended to handle negative values by mirroring around zero.

6. **Clamping:** If enabled, constrain all output values to 0.0–1.0.

### LUT Size Selection

| Size | Entries | Accuracy | File Size | Recommended Use |
|------|---------|----------|-----------|-----------------|
| 16 | 4,096 | Moderate | ~93 KB | Quick preview |
| 17 | 4,913 | Moderate | ~111 KB | Common Monitoring LUT |
| 32 | 32,768 | Good | ~742 KB | General use |
| 33 | 35,937 | Good | ~814 KB | Common standard |
| 48 | 110,592 | Very Good | ~2.5 MB | High quality |
| 64 | 262,144 | Excellent | ~5.9 MB | Demanding work |
| 65 | 274,625 | Excellent | ~6.2 MB | Maximum precision |

For most production work, the 33x33x33 cube, is the optimal balance of accuracy and compatibility. Sizes 17 and 33 are the most widely supported across NLEs. Use 64 or 65 only when the transform has complex non-linearities (such as combined rolloff with high EV compensation) that require more interpolation points for smooth gradients.

---

### Naming Convention

The LUT generator names files with all relevant parameters encoded:

```
GP-Log2_EV+1.8_Rec709_rolloff_33.cube
         │      │      │       └── LUT size
         │      │      └── Rolloff enabled
         │      └── Output color space
         └── EV compensation applied
```

When `_clamped` appears, output has been constrained to 0–1. When it is absent, the LUT is extended range.

---

*This white paper was prepared in conjunction with the GP-Log2 LUT Generator tool. The mathematical transforms described here are implemented directly in the tool's JavaScript source and match the behavior of the exported .cube LUT files.*

---

**Document Version:** 1.0
**Subject:** GP-Log2 Logarithmic Encoding and LUT-Based Color Grading
