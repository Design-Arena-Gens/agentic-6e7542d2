## Smart Tagger

Smart Tagger is an Unreal Engine editor plugin bundled with a marketing site built on Next.js. The plugin accelerates world-building workflows by batching gameplay tags, metadata stamps, and rename operations for any set of selected actors.

### Repository Layout

- `public/downloads/SmartTaggerPlugin` &mdash; ready-to-install Unreal Engine plugin source.
- `public/downloads/SmartTaggerPlugin.zip` &mdash; zipped delivery used by the website download CTA.
- `src/app` &mdash; statically generated marketing site deployed to Vercel.

### Plugin Highlights

- Toolbar button in the Level Editor that opens a custom Slate panel.
- Batch tag editor with append/replace modes and metadata stamping.
- Tokenised rename tool supporting `{BaseName}` and `{Index}` placeholders.
- Blueprint callable helper (`SmartApplyTags`) for automation pipelines.

### Installing in Unreal Engine

1. Copy `public/downloads/SmartTaggerPlugin` into `YourProject/Plugins/SmartTagger`.
2. Launch Unreal Editor, enable **Smart Tagger** under *Edit → Plugins*, and restart.
3. Access the tool from the Level Editor toolbar or call the Blueprint helper functions.

### Developing the Site

```bash
npm install
npm run dev
```

Visit `http://localhost:3000` for the UI, which serves the downloadable plugin and documentation.

### Building for Production

```bash
npm run build
npm run start
```

After a successful build, deploy directly to Vercel:

```bash
vercel deploy --prod --yes --token $VERCEL_TOKEN --name agentic-6e7542d2
```
