FROM ghcr.io/puppeteer/puppeteer:23.1.1 AS build

USER root

RUN corepack enable

# Add user so we don't need --no-sandbox.
RUN mkdir -p /home/pptruser/Downloads /app \
    && chown -R pptruser:pptruser /home/pptruser \
    && chown -R pptruser:pptruser /app

# Run everything after as non-privileged user.
USER pptruser

WORKDIR /app
COPY ["package.json", "package-lock.json*", "npm-shrinkwrap.json*", ".yarnrc.yml", "yarn.lock", "./yarn", "./"]
RUN cp -r /home/pptruser/node_modules ./node_modules


RUN yarn
USER root
RUN mkdir -p /home/pptruser/Downloads \
    && chown -R pptruser:pptruser /home/pptruser \
    && chown -R pptruser:pptruser /app
USER pptruser

# Run everything after as non-privileged user.
USER pptruser

COPY --chown=pptruser:pptruser . .

RUN yarn build

EXPOSE 3000
CMD yarn run drizzle-kit migrate && node build